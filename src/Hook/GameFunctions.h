#pragma once
#include "pch.h"
#include "Icetrix/Application.h"
#include "Icetrix/Events.h"
#include <Icetrix/Memory/PatternScan.h>
#include <appdata/helpers.h>
#include <appdata/pch-il2cpp.h>
#include "Utility.h"
#include "Game.h"
#include <Events.h>
#include <codecvt>

using namespace app;

class GameFunctions
{
public:
    GameFunctions()
    {
        g_sApp.dispatcher.sink<Icetrix::LayerEvent::Attach>().connect<&GameFunctions::AttachHook>(*this);
        g_sApp.dispatcher.sink<Icetrix::LayerEvent::Detach>().connect<&GameFunctions::DetachHook>(*this);
    }

    void AttachHook()
    {
        if (!checkStatus("Initialize", MH_Initialize()))
            return;

        FuncHook(GhostAI_Awake);
        FuncHook(GhostAI_Update);
        FuncHook(OuijaBoard_Start);
        FuncHook(DNAEvidence_Start);
        FuncHook(SceneManager_LoadScene_1);
        FuncHook(GameController_Start);
        FuncHook(GameController_Exit);
        FuncHook(Player_1_Update);
        FuncHook(Player_1_Awake);
        FuncHook(RewardManager_Awake);
        FuncHook(MissionManager_Awake);
        FuncHook(MainManager_Start);
        FuncHook(JournalController_OnEnable);
        FuncHook(JournalController_OnDisable);
        FuncHook(Time_get_timeScale);
        FuncHook(PhotonNetwork_SetMasterClient);
        FuncHook(FirstPersonController_FixedUpdate);

        // Audio
        FuncHook(HouseAmbientSoundController_PlaySound);
        //FuncHook(AudioSource_Play);
        //FuncHook(AudioSource_PlayOneShot);
        //FuncHook(AudioSource_PlayOneShot_1);

        FuncHook(PhotonView_RPC);
    }

    void DetachHook()
    {
        DeFuncHook(GhostAI_Awake);
        DeFuncHook(GhostAI_Update);
        DeFuncHook(OuijaBoard_Start);
        DeFuncHook(DNAEvidence_Start);
        DeFuncHook(SceneManager_LoadScene_1);
        DeFuncHook(GameController_Start);
        DeFuncHook(GameController_Exit);
        DeFuncHook(Player_1_Awake);
        DeFuncHook(Player_1_Update);
        DeFuncHook(RewardManager_Awake);
        DeFuncHook(MissionManager_Awake);
        DeFuncHook(MainManager_Start);
        DeFuncHook(JournalController_OnEnable);
        DeFuncHook(JournalController_OnDisable);
        DeFuncHook(Time_get_timeScale);
        DeFuncHook(FirstPersonController_FixedUpdate);
        //DeFuncHook(PhotonNetwork_SetMasterClient);

        // Audio
        DeFuncHook(HouseAmbientSoundController_PlaySound);
        //DeFuncHook(AudioSource_Play);
        //DeFuncHook(AudioSource_PlayOneShot);
        //DeFuncHook(AudioSource_PlayOneShot_1);

        DeFuncHook(PhotonView_RPC);
    }

    HOOK_DEF(void, GhostAI_Awake, (Phasmo::GhostAI* __this, MethodInfo* method))
    {
        oGhostAI_Awake(__this, NULL);
        g_sApp.dispatcher.trigger<Phasmo::Event::GhostUpdate>(__this);
    }

    HOOK_DEF(void, GhostAI_Update, (Phasmo::GhostAI* __this, MethodInfo* method))
    {
        oGhostAI_Update(__this, NULL);
        g_sApp.dispatcher.trigger<Phasmo::Event::GhostUpdate>(__this);
    }

    HOOK_DEF(void, OuijaBoard_Start, (OuijaBoard* __this, MethodInfo* method))
    {
        oOuijaBoard_Start(__this, NULL);
        g_sApp.dispatcher.trigger<Phasmo::Event::OuijaBoardUpdate>(__this);
    }

    HOOK_DEF(void, DNAEvidence_Start, (DNAEvidence* __this, MethodInfo* method))
    {
        g_sApp.dispatcher.trigger<Phasmo::Event::DNAEvidenceUpdate>(__this);
        return oDNAEvidence_Start(__this, NULL);
    }

    HOOK_DEF(void, SceneManager_LoadScene_1, (String* sceneName, MethodInfo* method))
    {
        g_sApp.dispatcher.trigger<Phasmo::Event::SceneManagerLoadScene>();
        return oSceneManager_LoadScene_1(sceneName, NULL);
    }

    HOOK_DEF(void, GameController_Exit, (GameController* __this, MethodInfo* method))
    {
        g_sApp.dispatcher.trigger<Phasmo::Event::GameControllerExit>();
        return oGameController_Exit(__this, NULL);
    }

    HOOK_DEF(void, RewardManager_Awake, (RewardManager* __this, MethodInfo* method))
    {
        g_sApp.dispatcher.trigger<Phasmo::Event::RewardManagerAwake>(__this);
        return oRewardManager_Awake(__this, NULL);
    }

    HOOK_DEF(void, Player_1_Update, (Phasmo::Player_1* __this, MethodInfo* method))
    {
        auto view = __this->fields.view;
        if (view->fields._Owner_k__BackingField && view->fields._Owner_k__BackingField->fields.IsLocal)
			g_sApp.dispatcher.trigger<Phasmo::Event::PlayerUpdate>(__this);

        return oPlayer_1_Update(__this, method);
    }

    HOOK_DEF(void, Player_1_Awake, (Phasmo::Player_1* __this, MethodInfo* method))
    {
        auto view = __this->fields.view;
        if (view->fields._Owner_k__BackingField && view->fields._Owner_k__BackingField->fields.IsLocal)
			g_sApp.dispatcher.trigger<Phasmo::Event::PlayerUpdate>(__this);

        return oPlayer_1_Awake(__this, method);
    }

    HOOK_DEF(IEnumerator*, MainManager_Start, (Phasmo::MainManager* __this, MethodInfo* method))
    {
        g_sApp.dispatcher.trigger<Phasmo::Event::MainManagerUpdate>(__this);
        return oMainManager_Start(__this, method);
    }

    HOOK_DEF(void, MissionManager_Awake, (Phasmo::MissionManager* __this, MethodInfo* method))
    {
        g_sApp.dispatcher.trigger<Phasmo::Event::MissionManagerUpdate>(__this);
        return oMissionManager_Awake(__this, method);
    }

    HOOK_DEF(void, JournalController_OnEnable, (JournalController* __this, MethodInfo* method))
    {
        g_sApp.dispatcher.trigger<Phasmo::Event::JournalControllerUpdate>(__this);
        oJournalController_OnEnable(__this, method);
    }
    HOOK_DEF(void, JournalController_OnDisable, (JournalController* __this, MethodInfo* method))
    {
        g_sApp.dispatcher.trigger<Phasmo::Event::JournalControllerUpdate>(__this);
        oJournalController_OnDisable(__this, method);
    }
    
    HOOK_DEF(float, Time_get_timeScale, (MethodInfo* method))
    {
        float timeScale = oTime_get_timeScale(method);
        g_sApp.dispatcher.trigger<Phasmo::Event::TimeScale>(&timeScale);
        Time_set_timeScale(timeScale, NULL);
        return timeScale;
    }

    HOOK_DEF(void, GameController_Start, (GameController* __this, MethodInfo* method))
    {
        g_sApp.dispatcher.trigger<Phasmo::Event::GameControllerStart>(__this);
        oGameController_Start(__this, method);
    }

    HOOK_DEF(void, HouseAmbientSoundController_PlaySound, (HouseAmbientSoundController* __this, app::Vector3 pos, int32_t clipID, MethodInfo* method))
    {
        LOG_INFO("[PlaySound] ClipID: " << clipID);
    }

    HOOK_DEF(void, AudioSource_Play, (AudioSource* __this, MethodInfo* method))
    {
        LOG_INFO("[AudioSource_Play] " << std::hex << __this);
    }

    HOOK_DEF(void, AudioSource_PlayOneShot, (AudioSource* __this, AudioClip* clip, MethodInfo* method))
    {
        LOG_INFO("[AudioSource_PlayOneShot] " << std::hex << __this << " | Clip: " << std::hex << clip);
    }

    HOOK_DEF(void, AudioSource_PlayOneShot_1, (AudioSource* __this, AudioClip* clip, float volumeScale, MethodInfo* method))
    {
        LOG_INFO("[AudioSource_PlayOneShot_1] " << std::hex << __this << " | Clip: " << std::hex << clip);
    }

    HOOK_DEF(bool, PhotonNetwork_SetMasterClient, (Player* masterClientPlayer, MethodInfo* method))
    {
        LOG_INFO("[SetMasterClient] " << masterClientPlayer->fields.actorNumber << " | Name: " << GetUTF8StringFromNETString(masterClientPlayer->fields.nickName));
        return oPhotonNetwork_SetMasterClient(masterClientPlayer, method);
    }

    HOOK_DEF(void, FirstPersonController_FixedUpdate, (FirstPersonController* __this, MethodInfo* method))
    {
        g_sApp.dispatcher.trigger<Phasmo::Event::FirstPersonControllerUpdate>(__this);
        return oFirstPersonController_FixedUpdate(__this, method);
    }

    HOOK_DEF(void, PhotonView_RPC, (PhotonView* __this, String* methodName, RpcTarget__Enum target, Object__Array* parameters, MethodInfo* method))
    {
        auto convertedMethodName = GetUTF8StringFromNETString(methodName);
        if (convertedMethodName.rfind("Completed", 0) == 0) {
			LOG_INFO("[RPC] " << convertedMethodName);
        }
        return oPhotonView_RPC(__this, methodName, target, parameters, method);
    }

public:
	static inline std::wstring_convert<std::codecvt_utf8_utf16<char16_t, 0x10FFFF, std::codecvt_mode::little_endian>, char16_t> UTF16_TO_UTF8;
	static inline std::string GetUTF8StringFromNETString(app::String* netString)
	{
		if (netString == NULL)
			return NULL;

		uint16_t* buffer = new uint16_t[netString->fields.m_stringLength + 1];
		memcpy(buffer, &netString->fields.m_firstChar, netString->fields.m_stringLength * sizeof(uint16_t));
		buffer[netString->fields.m_stringLength] = L'\0';
		std::string newString = UTF16_TO_UTF8.to_bytes((const char16_t*)buffer);

		delete[] buffer;

		return newString;
	}

};
