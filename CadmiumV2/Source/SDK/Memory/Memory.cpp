#include "Memory.h"
#include "Offsets.h"

std::string Memory::WideCharToString(const wchar_t* wideStr)
{
    if (!wideStr) return "";

    int bufferSize = WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, nullptr, 0, nullptr, nullptr);
    if (bufferSize == 0) {
        return "";
    }

    std::string result(bufferSize - 1, 0);
    WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, &result[0], bufferSize, nullptr, nullptr);
    return result;
}

std::string Memory::TCHARToString(const TCHAR* tcharStr)
{
#ifdef UNICODE
    return WideCharToString(tcharStr);
#else
    return std::string(tcharStr);
#endif
}

std::string Memory::FormatPath(const std::string& filePath)
{
    size_t lastSlashPos = filePath.find_last_of("\\/");
    if (lastSlashPos == std::string::npos) {
        return "";
    }

    std::string folderPath = filePath.substr(0, lastSlashPos); 
    size_t secondLastSlashPos = folderPath.find_last_of("\\/");
    if (secondLastSlashPos == std::string::npos) {
        return "";
    }

    return folderPath.substr(0, secondLastSlashPos + 1);
}

std::string Memory::GetProcessPathByPID()
{
    std::string path;

    MODULEENTRY32 moduleEntry = { sizeof(MODULEENTRY32) };
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, ProcessID);
    if (hSnapshot == INVALID_HANDLE_VALUE)
        return "";

    if (Module32First(hSnapshot, &moduleEntry)) {
        do {
            if (!_wcsicmp(moduleEntry.szModule, L"client.dll")) {
                CloseHandle(hSnapshot);
                path = FormatPath(TCHARToString(moduleEntry.szExePath));
                return path;
            }
        } while (Module32Next(hSnapshot, &moduleEntry));
    }
    CloseHandle(hSnapshot);
    return "";
}


int Memory::GetProcessIdByName()
{
    int ProcessID = 0;
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (Process32First(snapshot, &entry) == TRUE) {
        while (Process32Next(snapshot, &entry) == TRUE) {
            if (_wcsicmp(entry.szExeFile, TargetModuleName) == 0) {
                CloseHandle(snapshot);
                ProcessID = entry.th32ProcessID;
                return ProcessID;
            }
        }
    }

    CloseHandle(snapshot);
    return 0;
}

uintptr_t Memory::GetModuleBaseAddress(const wchar_t* moduleName)
{
    MODULEENTRY32 moduleEntry = { sizeof(MODULEENTRY32) };
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, ProcessID);
    if (hSnapshot == INVALID_HANDLE_VALUE)
        return 0;

    if (Module32First(hSnapshot, &moduleEntry)) {
        do {
            if (!_wcsicmp(moduleEntry.szModule, moduleName)) {
                CloseHandle(hSnapshot);

                return (DWORD_PTR)moduleEntry.modBaseAddr;
            }
        } while (Module32Next(hSnapshot, &moduleEntry));
    }
    CloseHandle(hSnapshot);
    return 0;
}

bool Memory::GetModule(const wchar_t* moduleName, GameModule& outModule)
{
    MODULEENTRY32 moduleEntry = { sizeof(MODULEENTRY32) };
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, ProcessID);
    if (hSnapshot == INVALID_HANDLE_VALUE)
        return false;

    if (Module32First(hSnapshot, &moduleEntry)) {
        do {
            if (!_wcsicmp(moduleEntry.szModule, moduleName)) {
                CloseHandle(hSnapshot);

                outModule.BaseAdress = (DWORD_PTR)moduleEntry.modBaseAddr;
                outModule.Size = moduleEntry.modBaseSize;

                return true;
            }
        } while (Module32Next(hSnapshot, &moduleEntry));
    }
    CloseHandle(hSnapshot);
    return false;
}



void Memory::InitContext()
{
    ProcessID = GetProcessIdByName();

    Driver = CreateFile(L"\\\\.\\km", GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

    if (Driver == INVALID_HANDLE_VALUE) {
        std::cout << "[Memory]: Failed to create our driver handle" << std::endl;
        exit(FAILED_CREATE_DRIVER_HANDLE);
    }
    else {
        std::cout << "[Memory]: Create driver handle complete" << std::endl;
    }

    if (!DRIVER::AttachToProcess(Driver, ProcessID)) {
        std::cout << "[Memory]: Failed to attach our driver handle" << std::endl;
        exit(FAILED_DRIVER_ATTACH);
    }
    else {
        std::cout << "[Memory]: Attach driver handle complete" << std::endl;
    }



    if (GetModule(ClientDllName, ClientDLL) && GetModule(EngineDllName, EngineDLL) && GetModule(ServerDllName, ServerDLL)) {
        std::cout << "[Memory]: Get base modules." << std::endl;
    }
    else {
        std::cout << "[Memory]: Failed getting base modules." << std::endl;
        exit(FAILED_GET_MODULE);
    }

    

    if (GamePath = GetProcessPathByPID(); GamePath == "") {
        std::cout << "[Memory]: Failed getting base game path" << std::endl;
        exit(FAILED_GET_PATH);
    }
    else {
        std::cout << "[Memory]: Get base game path complete: " << GamePath << std::endl;
    }
}

void Memory::CloseContext()
{
    CloseHandle(Driver);
}


Memory::Memory()
{
    InitContext();
}

Memory::~Memory()
{
    CloseContext();
}

void Memory::Update()
{
    inGame = Read<bool>(EngineDLL.BaseAdress + EngineOffsets::ptr_bIsInGame);
}

const int Memory::GetProcessID()
{
    return ProcessID;
}

const bool Memory::GetInGame()
{
    return inGame;
}
