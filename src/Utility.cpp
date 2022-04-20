#include "pch.h"
#include <Utility.h>
#include "Game.h"

RESOLVE_FUNC(Marshal_PtrToStringAnsi, app::String*, (void*, MethodInfo*), "\x48\x85\xC9\x75\x03\x33\xC0\xC3\xE9", "xxxxxxxxx");

app::String* CreateNETStringFromANSI(const char* string)
{
	return Marshal_PtrToStringAnsi((void*)string, NULL);
}

bool checkStatus(std::string name, MH_STATUS status)
{
    if (status != MH_OK && status != MH_ERROR_ALREADY_CREATED && status != MH_ERROR_ALREADY_INITIALIZED)
    {
        LOG_ERROR("[Hook::" << name << "] " << MH_StatusToString(status));
        return false;
    }

    return true;
}
