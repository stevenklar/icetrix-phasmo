#pragma once
#include <pch.h>
#include <iostream>
#include "Icetrix/Application.h"
#include "Icetrix/Events.h"
#include "Icetrix/Renderer.h"
#include <appdata/pch-il2cpp.h>
#include "Utility.h"
#include "ImHotkey.h"
#include "Game.h"

using namespace app;

class ESP
{
private:
	bool playerESP = true;
	bool ghostESP = true;
	bool boneESP = true;
	bool ouijaESP = true;
	bool carESP = true;

	Phasmo::GhostAI* ghost = nullptr;
	OuijaBoard* ouijaBoard = nullptr;
	DNAEvidence* bone = nullptr;
	Phasmo::GameController* gameController = nullptr;

public:
	ESP()
	{
		g_sApp.dispatcher.sink<Icetrix::Layer::MenuDefaultWindowEvent>().connect<&ESP::Menu>(*this);
        g_sApp.dispatcher.sink<Icetrix::Layer::MenuDrawEvent>().connect<&ESP::Render>(*this);
		g_sApp.dispatcher.sink<Phasmo::Event::GameControllerStart>().connect<&ESP::GameControllerUpdate>(*this);
		g_sApp.dispatcher.sink<Phasmo::Event::GhostUpdate>().connect<&ESP::GhostUpdate>(*this);
		g_sApp.dispatcher.sink<Phasmo::Event::OuijaBoardUpdate>().connect<&ESP::OuijaUpdate>(*this);
		g_sApp.dispatcher.sink<Phasmo::Event::DNAEvidenceUpdate>().connect<&ESP::BoneUpdate>(*this);
        g_sApp.dispatcher.sink<Phasmo::Event::MainManagerUpdate>().connect<&ESP::GarbageCollect>(*this);
		g_sApp.dispatcher.sink<Icetrix::Hook::InputEvent::hwndProc>().connect<&ESP::Input>(*this);
	}

	void GhostUpdate(Phasmo::Event::GhostUpdate e) { this->ghost = e.ghost; }
	void OuijaUpdate(Phasmo::Event::OuijaBoardUpdate e) { this->ouijaBoard = e.ouijaBoard; }
	void BoneUpdate(Phasmo::Event::DNAEvidenceUpdate e) { this->bone = e.bone; }
	void GameControllerUpdate(Phasmo::Event::GameControllerStart e) { this->gameController = (Phasmo::GameController*)e.gameController; }
	void GarbageCollect()
	{
		LOG_INFO("[ESP::GarbageCollect]");
		gameController = nullptr;
		ghost = nullptr;
		ouijaBoard = nullptr;
		bone = nullptr;
	}

    void Menu()
    {
		ImGui::Checkbox("Player ESP", &playerESP);
		ImGui::Checkbox("Ghost ESP", &ghostESP);
		ImGui::Checkbox("Bone ESP", &boneESP);
		ImGui::Checkbox("Ouija ESP", &ouijaESP);
    }

	void Input(const Icetrix::Hook::InputEvent::hwndProc& input)
	{
		//ImGui_ImplWin32_WndProcHandler(input.hWnd, input.uMsg, input.wParam, input.lParam);
		if (ImGui::GetCurrentContext() == NULL)
			return;

		auto wParam = input.wParam;
		ImGuiIO& io = ImGui::GetIO();

		switch (input.uMsg)
		{
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
			if (wParam < 256)
				io.KeysDown[wParam] = 1;
			break;
		case WM_KEYUP:
		case WM_SYSKEYUP:
			if (wParam < 256)
				io.KeysDown[wParam] = 0;
			break;
		}

		auto hotkey = ImHotKey::GetHotKey(hotkeys.data(), hotkeys.size());
		if (hotkey == HOTKEY_PLAYERESP) playerESP = !playerESP;
		if (hotkey == HOTKEY_GHOSTESP) ghostESP = !ghostESP;
		if (hotkey == HOTKEY_BONE) boneESP = !boneESP;
		if (hotkey == HOTKEY_OUIJABOARD) ouijaESP = !ouijaESP;

		for (int i = 0; i < IM_ARRAYSIZE(io.KeysDown); i++) io.KeysDown[i] = false;
	}

	void Render()
	{
		g_sRenderer->BeginScene();

		if (playerESP) TRY(RenderPlayers());
		if (ghostESP) TRY(RenderGhost());
		if (boneESP) TRY(RenderBone());
		if (ouijaESP) TRY(RenderOuija());

		g_sRenderer->EndScene();
	}

	void RenderPlayers()
	{
		if (!gameController)
			return;

		auto players = gameController->fields.playersData;

		for (size_t i = 0; i < players->fields._size; i++)
		{
			auto playerData = players->fields._items->vector[i];
			renderEsp(GetUTF8StringFromNETString((app::String*)playerData->fields.playerName), (Component_1*)playerData->fields.player, ImColor(0, 255, 0));
		}
	}

	void RenderGhost()
	{
		if (ghost)
			renderEsp("Ghost", (Component_1*)ghost, ImColor(0, 0, 255));
	}

	void RenderBone()
	{
		if (bone)
			renderEsp("Bone", (Component_1*)bone, ImColor(250, 250, 255));
	}

	void RenderOuija()
	{
		if (ouijaBoard)
			renderEsp("Ouija", (Component_1*)ouijaBoard, ImColor(88, 179, 197));
	}

private:
	void renderEsp(std::string name, Component_1* component, ImColor color = ImColor(255, 255, 255), float rel = 0.f)
	{
		if (!app::Behaviour_get_isActiveAndEnabled((Behaviour*)component, NULL)) return;

		Transform transform = *app::Component_1_get_transform(component, NULL);
		app::Vector3 position = app::Transform_get_position(&transform, NULL);

		renderEsp(name, position, color, rel);
	}

	void renderEsp(std::string name, app::Vector3 position, ImColor color = ImColor(255, 255, 255), float rel = 0.f)
	{
		Camera camera = *app::Camera_get_main(NULL);
		app::Vector3 screenPoint = app::Camera_WorldToScreenPoint_1(&camera, position, NULL);
		//int height = app::Screen_get_height(NULL);
		app::Resolution resolution = app::Screen_get_currentResolution(NULL);
		int height = resolution.m_Height;

		if (screenPoint.z <= 0.f)
			return;

		g_sRenderer->RenderText(name, { screenPoint.x, height - screenPoint.y + rel }, 15.0f, color, true);
	}

	/*
	app::Vector3 camera = Transform_get_position((Transform*)Component_1_get_transform((Component_1*)Camera_get_current(NULL), NULL), NULL);
	app::Vector3 position = Transform_get_position((Transform*)Component_1_get_transform((Component_1*)ghost, NULL), NULL);
	char* distance = getDistance(camera, position);
	renderEsp(distance, (Component_1*)ghost, ImColor(0, 0, 255), 15.f);

	char* getDistance(app::Vector3 a, app::Vector3 b)
	{
		char distance[17];
		_gcvt_s(distance, sizeof(distance), round(Vector3_Distance(a, b, NULL)) - 1, 8);
		distance[strlen(distance) - 1] = (char)"";

		return distance;
	}
	*/

private:
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
