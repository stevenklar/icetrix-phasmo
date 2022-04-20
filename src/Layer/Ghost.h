#pragma once
#include "Icetrix/Application.h"
#include "Icetrix/Events.h"
#include <appdata/pch-il2cpp.h>

#include <Windows.h>
#include <codecvt>
#include <imgui_internal.h>
#include <thread>
#include <appdata\helpers.h>

#include <Game.h>

using namespace app;

class Ghost
{
private:
	Phasmo::GhostAI* ghost = nullptr;
	Phasmo::Player_1* localPlayer = nullptr;
public:
    Ghost()
    {
        g_sApp.dispatcher.sink<Icetrix::LayerEvent::Attach>().connect<&Ghost::Attach>(*this);
        g_sApp.dispatcher.sink<Icetrix::LayerEvent::Detach>().connect<&Ghost::Detach>(*this);
        g_sApp.dispatcher.sink<Icetrix::Layer::MenuDrawEvent>().connect<&Ghost::Menu>(*this);
		g_sApp.dispatcher.sink<Icetrix::Layer::MenuDrawEvent>().connect<&Ghost::Warning>(*this);
        g_sApp.dispatcher.sink<Icetrix::Layer::MenuDefaultWindowEvent>().connect<&Ghost::InMenu>(*this);
        //g_sApp.dispatcher.sink<Phasmo::Event::PlayerUpdate>().connect<&Ghost::Flashlight>(*this);

		g_sApp.dispatcher.sink<Phasmo::Event::GhostUpdate>().connect<&Ghost::GhostUpdate>(*this);
		g_sApp.dispatcher.sink<Phasmo::Event::PlayerUpdate>().connect<&Ghost::PlayerUpdate>(*this);
		g_sApp.dispatcher.sink<Phasmo::Event::SceneManagerLoadScene>().connect<&Ghost::GarbageCollect>(*this);
		g_sApp.dispatcher.sink<Phasmo::Event::GameControllerExit>().connect<&Ghost::GarbageCollect>(*this);
		g_sApp.dispatcher.sink<Phasmo::Event::RewardManagerAwake>().connect<&Ghost::GarbageCollect>(*this);
        g_sApp.dispatcher.sink<Phasmo::Event::MainManagerUpdate>().connect<&Ghost::GarbageCollect>(*this);
    }

    Icetrix::Feature* feature = new Icetrix::Feature{ "Ghost Info", true };
    void Attach() { g_sFeatures->Push(feature); }
    void Detach() { delete feature; }

	void GarbageCollect()
	{
		LOG_INFO("[Ghost::GarbageCollect]");
		localPlayer = nullptr;
		ghost = nullptr;
	}
	void GhostUpdate(Phasmo::Event::GhostUpdate e) { this->ghost = e.ghost; }
	void PlayerUpdate(Phasmo::Event::PlayerUpdate e) { this->localPlayer = e.localPlayer; }

    void InMenu()
    {
        if (!localPlayer)
            return;
    }

    void Warning()
    {
        if (!g_sFeatures->Get(feature->label)->enabled)
            return;

        if (!ghost)
            return;
        
        if (ghost->fields.isHunting)
        {
			app::Resolution resolution = app::Screen_get_currentResolution(NULL);

            g_sRenderer->BeginScene();
			g_sRenderer->RenderText("GHOST IS HUNTING", { resolution.m_Width / 2.f, 10.f }, 35.f, ImColor(0, 0, 255), true);
            g_sRenderer->EndScene();
        }
    }

    /*
    // Permanent help flashlight ;-)
    void Flashlight(Phasmo::Event::PlayerUpdate e)
    {
        app::PCFlashlight* flashlight = (app::PCFlashlight*)e.localPlayer->fields.pcFlashlight;
        PCFlashlight_EnableOrDisableLight(flashlight, true, true, NULL);
    }
    */

    void Menu()
    {
        if (!feature->enabled)
            return;

        if (!ghost)
            return;
        
        Phasmo::GhostInfo* ghostInfo = ghost->fields.ghostInfo;

        if (!ghostInfo)
            return;

		Phasmo::GhostTraits gTraits = ghostInfo->fields.ghostTraits;
		if (!gTraits.GhostName)
            return;

        bool enabled = feature->enabled;
        if (ImGui::Begin("Ghost Info", &enabled, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse))
        {
			ImGui::Text("Name: %s", GetUTF8StringFromNETString(gTraits.GhostName).c_str());
			ImGui::Text("Type: %s", ConvertGhostType(gTraits.ghostType).c_str());
			ImGui::Text("State: %s", ConvertGhostState(ghost->fields.state).c_str());
			ImGui::Text("Room: %s", getGhostLocation(ghostInfo->fields.favouriteRoom).c_str());
			ImGui::Text("Age: %d", gTraits.ghostAge);
			//ImGui::Text("Male: %s", (gTraits.isMale) ? "Yes" : "No");
			ImGui::Text("Shy: %s", (gTraits.isShy) ? "Yes" : "No");
			ImGui::Text("Hunting: %s", (ghost->fields.isHunting) ? "Yes" : "No");
			ImGui::Text("Can Hunt: %s", (ghost->fields.canEnterHuntingMode) ? "Yes" : "No");
			ImGui::Text("Can Attack: %s", (ghost->fields.canAttack) ? "Yes" : "No");
			//ImGui::Text("Chasing Player: %s", (ghost->fields.isChasingPlayer) ? "Yes" : "No");

            ImGui::End();
        }

    }

private:
    std::string ConvertGhostState(Phasmo::GhostAI_States__Enum state)
    {
        switch (state)
        {
        case Phasmo::idle:
            return "idle";
        case Phasmo::wander:
            return "wander";
        case Phasmo::hunting:
            return "hunting";
        case Phasmo::favouriteRoom:
			return "favouriteRoom";
        case Phasmo::light:
			return "light";
        case Phasmo::door:
			return "door";
        case Phasmo::throwing:
			return "throwing";
        case Phasmo::fusebox:
			return "fusebox";
        case Phasmo::appear:
			return "appear";
        case Phasmo::doorKnock:
			return "doorKnock";
        case Phasmo::windowKnock:
			return "windowKnock";
        case Phasmo::carAlarm:
			return "carAlarm";
        case Phasmo::radio:
			return "radio";
        case Phasmo::flicker:
			return "flicker";
        case Phasmo::cctv:
			return "cctv";
        case Phasmo::randomEvent:
			return "randomEvent";
        case Phasmo::GhostAbility:
			return "GhostAbility";
        case Phasmo::mannequin:
			return "mannequin";
        case Phasmo::teleportObject:
			return "teleportObject";
        }
        return "Unknown";
    }

    std::string ConvertGhostType(Phasmo::GhostTraits_Type__Enum type)
    {
        switch (type)
        {
        case Phasmo::GhostTraits_Type__Enum::Spirit:
            return "Spirit (EMF 5, Box, Book)";
        case Phasmo::GhostTraits_Type__Enum::Wraith:
            return "Wraith (EMF 5, Box, D.O.T.S.)";
        case Phasmo::GhostTraits_Type__Enum::Phantom:
            return "Phantom (Box, Fingerprints, D.O.T.S.)";
        case Phasmo::GhostTraits_Type__Enum::Poltergeist:
            return "Poltergeist (Box, Fingerprints, Book)";
        case Phasmo::GhostTraits_Type__Enum::Banshee:
            return "Banshee (Fingerprints, Orb, D.O.T.S.)";
        case Phasmo::GhostTraits_Type__Enum::Jinn:
            return "Jinn (EMF 5, Fingerprints, Freezing Temp)";
        case Phasmo::GhostTraits_Type__Enum::Mare:
            return "Mare (Box, Orb, Book)";
        case Phasmo::GhostTraits_Type__Enum::Revenant:
            return "Revenant (Orb, Book, Freezing Temp)";
        case Phasmo::GhostTraits_Type__Enum::Shade:
            return "Shade (EMF 5, Book, Freezing Temp)";
        case Phasmo::GhostTraits_Type__Enum::Demon:
            return "Demon (Fingerprints, Book, Freezing Temp)";
        case Phasmo::GhostTraits_Type__Enum::Yurei:
            return "Yurei (Orb, Freezing Temp, D.O.T.S.)";
        case Phasmo::GhostTraits_Type__Enum::Oni:
            return "Oni (EMF 5, Freezing Temp, D.O.T.S.)";
        case Phasmo::GhostTraits_Type__Enum::Yokai:
            return "Yokai (Box, Orb, D.O.T.S)";
        case Phasmo::GhostTraits_Type__Enum::Hantu:
            return "Hantu (Fingerprints, Orb, Freezing Temp)";
        case Phasmo::GhostTraits_Type__Enum::Goryo:
            return "Goryo (EMF 5, Fingerprints, D.O.T.S.)";
        case Phasmo::GhostTraits_Type__Enum::Myling:
            return "Myling (EMF 5, Fingerprints, Book)";
        case Phasmo::GhostTraits_Type__Enum::Onryo:
			return "Onryo (Box, Orb, Freezing Temp)";
        case Phasmo::GhostTraits_Type__Enum::TheTwins:
			return "TheTwins (EMF 5, Box, Freezing Temp)";
		case Phasmo::GhostTraits_Type__Enum::Raiju:
			return "Raiju (EMF 5, Orb, D.O.T.S.)";
		case Phasmo::GhostTraits_Type__Enum::Obake:
			return "Obake (EMF 5, Fingerprints, Orb)";
        }

        return "";
    }

    std::string getGhostLocation(Phasmo::LevelRoom* room)
    {
        if (!room || !room->fields.roomName) return "";

        std::string floor;
        switch (room->fields.floorType)
        {
        case 0x0:
            floor = "Basement";
            break;
        case 0x1:
            floor = "1. Floor";
            break;
        case 0x2:
            floor = "2. Floor";
            break;
        default:
            return "";
        }

        return floor + ": " + GetUTF8StringFromNETString(room->fields.roomName);
    }

	std::wstring_convert<std::codecvt_utf8_utf16<char16_t, 0x10FFFF, std::codecvt_mode::little_endian>, char16_t> UTF16_TO_UTF8;
    std::string GetUTF8StringFromNETString(Phasmo::String* netString)
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
