#pragma once
#include "pch.h"
#include <appdata/pch-il2cpp.h>
#include <appdata/il2cpp-appdata.h>

#define FuncHook(a) \
		if (checkStatus(#a, MH_CreateHook(app:: ## a, &h ## a, reinterpret_cast<LPVOID*>(&o ## a)))) \
			checkStatus(#a, MH_EnableHook(app:: ## a));

#define DeFuncHook(a) \
        checkStatus(#a, MH_DisableHook(app:: ## a));

#define HOOK_DEF(a, b, c) \
    typedef a (*t ## b) c; \
    static inline t ## b o ## b = NULL; \
    static a h ## b ## c

app::String* CreateNETStringFromANSI(const char* string);
bool checkStatus(std::string name, MH_STATUS status);
