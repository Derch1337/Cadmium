#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <cstdint>


namespace DRIVER {
    namespace CODES {
        constexpr ULONG attach = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_SPECIAL_ACCESS);
        constexpr ULONG read = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_BUFFERED, FILE_SPECIAL_ACCESS);
        constexpr ULONG write = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x802, METHOD_BUFFERED, FILE_SPECIAL_ACCESS);
    }

    struct Request {
        HANDLE process_id;
        PVOID target;
        PVOID buffer;
        SIZE_T size;
        SIZE_T return_size;
    };  

    inline bool AttachToProcess(HANDLE driver_handle, const DWORD pid) {
        Request r;
        r.process_id = reinterpret_cast<HANDLE>(pid);
        return DeviceIoControl(driver_handle, CODES::attach, &r, sizeof(r), &r, sizeof(r), nullptr, nullptr);
    }

    template <class T>
    inline T ReadMemory(HANDLE driver_handle, const std::uintptr_t addr) {
        T temp = {};

        Request r;
        r.target = reinterpret_cast<PVOID>(addr);
        r.buffer = &temp;
        r.size = sizeof(T);

        DeviceIoControl(driver_handle, CODES::read, &r, sizeof(r), &r, sizeof(r), nullptr, nullptr);

        return temp;
    }

    template <class T>
    inline void WriteMemory(HANDLE driver_handle, const std::uintptr_t addr, const T& value) {
        Request r;
        r.target = reinterpret_cast<PVOID>(addr);
        r.buffer = (PVOID)&value;
        r.size = sizeof(T);

        DeviceIoControl(driver_handle, CODES::write, &r, sizeof(r), &r, sizeof(r), nullptr, nullptr);
    }
}