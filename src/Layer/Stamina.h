#pragma once
#include "Icetrix/Application.h"
#include "Icetrix/Events.h"
#include <appdata/pch-il2cpp.h>
#include <imgui_internal.h>
#include <appdata\helpers.h>
#include "Utility.h"
#include "Game.h"

class Stamina
{
public:
    Stamina()
    {
        g_sApp.dispatcher.sink<Icetrix::LayerEvent::Attach>().connect<&Stamina::Attach>(*this);
        g_sApp.dispatcher.sink<Icetrix::LayerEvent::Detach>().connect<&Stamina::Detach>(*this);
        g_sApp.dispatcher.sink<Icetrix::LayerEvent::Attach>().connect<&Stamina::Hook>(*this);
        g_sApp.dispatcher.sink<Icetrix::LayerEvent::Detach>().connect<&Stamina::Unhook>(*this);
    }

    static inline Icetrix::Feature* feature = new Icetrix::Feature{ "Stamina", true };
    void Attach() { g_sFeatures->Push(feature); }
    void Detach() { delete feature; }

    void Hook()
    {
        if (!checkStatus("Initialize", MH_Initialize()))
            return;

        FuncHook(PCStamina_Update);
    }

    void Unhook()
    {
        DeFuncHook(PCStamina_Update);
    }

    HOOK_DEF(void, PCStamina_Update, (PCStamina* playerStamina, MethodInfo* method))
    {
        if (feature->enabled)
            return;

        return oPCStamina_Update(playerStamina, method);
    }
};

