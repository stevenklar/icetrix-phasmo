#pragma once
#include "pch.h"
#include "Icetrix/Application.h"
#include "Icetrix/Events.h"
#include <appdata/helpers.h>
#include <appdata/pch-il2cpp.h>
#include "Utility.h"
#include "Game.h"
#include <iostream>
#include <fstream>

using namespace app;

class AntiCheat
{
public:
	AntiCheat()
	{
        g_sApp.dispatcher.sink<Icetrix::LayerEvent::Attach>().connect<&AntiCheat::Hook>(*this);
        g_sApp.dispatcher.sink<Icetrix::LayerEvent::Detach>().connect<&AntiCheat::Unhook>(*this);
	}

    void Hook()
    {
        if (!checkStatus("Initialize", MH_Initialize()))
            return;

        FuncHook(ADetector_get_CheatDetected);
        FuncHook(ADetector_OnCheatDetected);
    }

    void Unhook()
    {
        DeFuncHook(ADetector_get_CheatDetected);
        DeFuncHook(ADetector_OnCheatDetected);
    }

    //DO_APP_FUNC(0x0037F9D0, bool, ADetector_get_CheatDetected, (ADetector* __this, MethodInfo* method));
    HOOK_DEF(bool, ADetector_get_CheatDetected, (ADetector* __this, MethodInfo* method))
    {
        LOG_INFO("[Hook::ADetector_get_CheatDetected] " << ((oADetector_get_CheatDetected(__this, method)) ? "True" : "False"));
        return false;
    }

    //DO_APP_FUNC(0x00241A20, void, ADetector_OnCheatDetected, (ADetector* __this, MethodInfo* method));
    HOOK_DEF(void, ADetector_OnCheatDetected, (ADetector* __this, MethodInfo* method))
    {
        // This will be called a lot.
    }
};