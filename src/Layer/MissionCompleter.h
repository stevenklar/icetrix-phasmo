#pragma once
#include "Icetrix/Application.h"
#include "Icetrix/Events.h"
#include <appdata/pch-il2cpp.h>
#include <Game.h>
#include <Icetrix.h>
#include <Utility.h>
#include <codecvt>
#include <Events.h>

app::String* CreateNETStringFromANSI(const char* string);

class MissionCompleter
{
private:
	Phasmo::MissionManager* missionManager = nullptr;
public:
	MissionCompleter()
	{
		g_sApp.dispatcher.sink<Icetrix::LayerEvent::Attach>().connect<&MissionCompleter::Attach>(*this);
		g_sApp.dispatcher.sink<Icetrix::LayerEvent::Detach>().connect<&MissionCompleter::Detach>(*this);
        g_sApp.dispatcher.sink<Icetrix::Layer::MenuDrawEvent>().connect<&MissionCompleter::Render>(*this);
		g_sApp.dispatcher.sink<Phasmo::Event::MissionManagerUpdate>().connect<&MissionCompleter::MissionManagerUpdate>(*this);
		g_sApp.dispatcher.sink<Phasmo::Event::MainManagerUpdate>().connect<&MissionCompleter::GarbageCollect>(*this);
	}

    Icetrix::Feature* feature = new Icetrix::Feature{ "Mission Manager", true };
    void Attach() { g_sFeatures->Push(feature); }
    void Detach() { delete feature; }
	void MissionManagerUpdate(Phasmo::Event::MissionManagerUpdate e) { this->missionManager = e.missionManager; }
	void GarbageCollect() { this->missionManager = nullptr; }

	void Render()
	{
        if (!feature->enabled)
            return;

		if (!missionManager)
			return;

		Phasmo::List_1_Mission_* missions = missionManager->fields.currentMissions;
		if (!missions)
			return;
		
		auto* missionArray = missions->fields._items;
		if (!missionArray)
			return;

		if (missions->fields._size == 0)
			return;

		int uncompletedMissionCount = 0;
		for (size_t i = 0; i <= 3; i++)
		{
			if (missionArray->vector[i])
				if (!missionArray->vector[i]->fields.completed)
					uncompletedMissionCount++;
		}

		if (uncompletedMissionCount == 0)
			return;

		bool enabled = feature->enabled;
		if (ImGui::Begin("Missions", &enabled, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse))
		{
			for (size_t i = 0; i <= 3; i++)
			{
				if (missionArray->vector[i])
					if (!missionArray->vector[i]->fields.completed && missionArray->vector[i]->fields.missionName)
						if (ImGui::Button(GetUTF8StringFromNETString((app::String*)missionArray->vector[i]->fields.missionName).c_str()))
							completeMissionByID(missionArray->vector[i]->fields.view, missionArray->vector[i]);

			}

			ImGui::End();
		}
	}

private:
	void completeMissionByID(Phasmo::PhotonView* view, Phasmo::Mission* mission)
	{
		auto klass = mission->klass;
		LOG_INFO("[MissionDump]: " << klass->_0.name);
		const char* klassName = klass->_0.name;

		if (0 == _stricmp(klassName, "MissionGhostType"))
			return app::Mission_Completed((app::Mission*)mission, NULL);
			//return app::PhotonView_RPC((app::PhotonView*)view, CreateNETStringFromANSI("CheckMissionComplete"), RpcTarget__Enum::RpcTarget__Enum_AllBuffered, NULL, NULL);

		if (0 == _stricmp(klassName, "MissionGhostEvent"))
			return app::PhotonView_RPC((app::PhotonView*)view, CreateNETStringFromANSI("CompletedGhostEventMissionSync"), RpcTarget__Enum::RpcTarget__Enum_AllBuffered, NULL, NULL);

		if (0 == _stricmp(klassName, "MissionCapturePhoto"))
			return app::PhotonView_RPC((app::PhotonView*)view, CreateNETStringFromANSI("CompletedCapturePhotoMissionSync"), RpcTarget__Enum::RpcTarget__Enum_AllBuffered, NULL, NULL);

		if (0 == _stricmp(klassName, "MissionCrucifix"))
			return app::PhotonView_RPC((app::PhotonView*)view, CreateNETStringFromANSI("CompletedCrucifixMissionSync"), RpcTarget__Enum::RpcTarget__Enum_AllBuffered, NULL, NULL);

		if (0 == _stricmp(klassName, "MissionBurnSage"))
			return app::PhotonView_RPC((app::PhotonView*)view, CreateNETStringFromANSI("CompletedBurnSageMissionSync"), RpcTarget__Enum::RpcTarget__Enum_AllBuffered, NULL, NULL);

		if (0 == _stricmp(klassName, "MissionMotionSensor"))
			return app::PhotonView_RPC((app::PhotonView*)view, CreateNETStringFromANSI("CompletedMotionMissionSync"), RpcTarget__Enum::RpcTarget__Enum_AllBuffered, NULL, NULL);

		if (0 == _stricmp(klassName, "MissionEMFEvidence"))
			return app::PhotonView_RPC((app::PhotonView*)view, CreateNETStringFromANSI("CompletedEMFMissionSync"), RpcTarget__Enum::RpcTarget__Enum_AllBuffered, NULL, NULL);

		if (0 == _stricmp(klassName, "MissionSalt"))
			return app::PhotonView_RPC((app::PhotonView*)view, CreateNETStringFromANSI("CompletedSaltMissionSync"), RpcTarget__Enum::RpcTarget__Enum_AllBuffered, NULL, NULL);

		if (0 == _stricmp(klassName, "MissionAverageSanity"))
			return app::PhotonView_RPC((app::PhotonView*)view, CreateNETStringFromANSI("CompletedAverageSanityMissionSync"), RpcTarget__Enum::RpcTarget__Enum_AllBuffered, NULL, NULL);

		if (0 == _stricmp(klassName, "MissionCandle"))
			return app::PhotonView_RPC((app::PhotonView*)view, CreateNETStringFromANSI("CompletedCandleMissionSync"), RpcTarget__Enum::RpcTarget__Enum_AllBuffered, NULL, NULL);

		if (0 == _stricmp(klassName, "MissionEscapeGhost"))
			return app::PhotonView_RPC((app::PhotonView*)view, CreateNETStringFromANSI("CompletedEscapeGhostMissionSync"), RpcTarget__Enum::RpcTarget__Enum_AllBuffered, NULL, NULL);

		if (0 == _stricmp(klassName, "MissionHuntSmudge"))
			return app::PhotonView_RPC((app::PhotonView*)view, CreateNETStringFromANSI("CompletedMissionHuntSmudgeMissionSync"), RpcTarget__Enum::RpcTarget__Enum_AllBuffered, NULL, NULL);

		if (0 == _stricmp(klassName, "MissionParabolic"))
			return app::PhotonView_RPC((app::PhotonView*)view, CreateNETStringFromANSI("CompletedParabolicMissionSync"), RpcTarget__Enum::RpcTarget__Enum_AllBuffered, NULL, NULL);

		/*
		if (0 == _stricmp(klassName, "MissionDirtyWater"))
			return app::PhotonView_RPC((app::PhotonView*)view, CreateNETStringFromANSI("CompletedDirtyWaterMissionSync"), RpcTarget__Enum::RpcTarget__Enum_AllBuffered, NULL, NULL);
		if (0 == _stricmp(klassName, "MissionVictimName"))
			return app::PhotonView_RPC((app::PhotonView*)view, CreateNETStringFromANSI("CompletedVictimNameMissionSync"), RpcTarget__Enum::RpcTarget__Enum_AllBuffered, NULL, NULL);
		if (0 == _stricmp(klassName, "MissionTemperature"))
			return app::PhotonView_RPC((app::PhotonView*)view, CreateNETStringFromANSI("CompletedTemperatureMissionSync"), RpcTarget__Enum::RpcTarget__Enum_AllBuffered, NULL, NULL);
		*/

		LOG_ERROR("[MissionCompleter] Unkown Mission: " << klassName);
	}

	std::wstring_convert<std::codecvt_utf8_utf16<char16_t, 0x10FFFF, std::codecvt_mode::little_endian>, char16_t> UTF16_TO_UTF8;
	std::string GetUTF8StringFromNETString(app::String* netString)
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
