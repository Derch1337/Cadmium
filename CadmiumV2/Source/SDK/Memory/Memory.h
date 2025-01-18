#pragma once
#include "IDriver.h"
#include <string>

#include "Module.h"
#include <iostream>


struct MemoryPage
{
    char bytes[8192];
};


class Memory
{
public:
    GameModule ClientDLL;
    GameModule EngineDLL;
    GameModule ServerDLL;

    std::string GamePath = "";/*example: c:\game\Counter - Strike Source\cstrike\*/

private:
    HANDLE Driver = nullptr;
    const wchar_t* ClientDllName = L"client.dll";
    const wchar_t* EngineDllName = L"engine.dll";
    const wchar_t* ServerDllName = L"server.dll";
    const wchar_t* TargetModuleName = L"hl2.exe";
    int ProcessID = 0;
    bool inGame = false;

    std::string WideCharToString(const wchar_t* wideStr);//shit code
    std::string TCHARToString(const TCHAR* tcharStr);//shit code
    std::string FormatPath(const std::string& filePath);//shit code
    std::string GetProcessPathByPID();//shit code

    int GetProcessIdByName();
    uintptr_t GetModuleBaseAddress(const wchar_t* moduleName);

    bool GetModule(const wchar_t* moduleName, GameModule& outModule);

    void InitContext();
    void CloseContext();


public:
    Memory();
    ~Memory();

    void Update();

    template <class T>
    const T Read(uintptr_t addr) {
        return DRIVER::ReadMemory<T>(Driver, addr);
    }

    template <class T>
    void Write(uintptr_t addr, T& value) {
        //DRIVER::WriteMemory<T>(Driver, addr, value);
    }

    const int GetProcessID();

    const bool GetInGame();

    
};

