#pragma once
#include <string>


enum DriverErrors
{
    SUCCESS = 0,
    FAILED_CREATE_DRIVER_HANDLE = 100,
    FAILED_DRIVER_ATTACH,
    FAILED_GET_MODULE,
    FAILED_GET_PATH,
};

struct GameModule
{
	uintptr_t BaseAdress;
	unsigned int Size;
};