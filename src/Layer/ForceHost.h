#pragma once
#include "Icetrix/Application.h"
#include "Icetrix/Events.h"
#include <appdata/pch-il2cpp.h>
#include <imgui_internal.h>
#include <appdata\helpers.h>
#include "Utility.h"
#include "Game.h"

class ForceHost
{
public:
    ForceHost()
    {
        g_sApp.dispatcher.sink<Icetrix::LayerEvent::Attach>().connect<&ForceHost::Attach>(*this);
        g_sApp.dispatcher.sink<Icetrix::LayerEvent::Detach>().connect<&ForceHost::Detach>(*this);
        g_sApp.dispatcher.sink<Icetrix::LayerEvent::Attach>().connect<&ForceHost::Hook>(*this);
        g_sApp.dispatcher.sink<Icetrix::LayerEvent::Detach>().connect<&ForceHost::Unhook>(*this);
    }

    static inline Icetrix::Feature* feature = new Icetrix::Feature{ "Force Host", false };
    void Attach() { g_sFeatures->Push(feature); }
    void Detach() { delete feature; }

    void Hook()
    {
        if (!checkStatus("Initialize", MH_Initialize()))
            return;

        FuncHook(PhotonNetwork_get_IsMasterClient);
        FuncHook(PhotonView_get_IsOwnerActive);
    }

    void Unhook()
    {
        DeFuncHook(PhotonNetwork_get_IsMasterClient);
        DeFuncHook(PhotonView_get_IsOwnerActive);
    }

    // DO_APP_FUNC(0x0073A310, bool, PhotonNetwork_get_IsMasterClient, (MethodInfo * method));
	HOOK_DEF(bool, PhotonNetwork_get_IsMasterClient, (MethodInfo* method))
    {
        if (feature->enabled)
        {
			auto localPlayer = app::PhotonNetwork_get_LocalPlayer(NULL);
			app::PhotonNetwork_SetMasterClient(localPlayer, NULL);
            return true;
        }

        return oPhotonNetwork_get_IsMasterClient(method);
    }

    //DO_APP_FUNC(0x01EEC0C0, bool, PhotonView_get_IsOwnerActive, (PhotonView* __this, MethodInfo* method));
    HOOK_DEF(bool, PhotonView_get_IsOwnerActive, (PhotonView* __this, MethodInfo* method))
    {
        if (feature->enabled)
            return true;

        return oPhotonView_get_IsOwnerActive(__this, method);
    }

};
