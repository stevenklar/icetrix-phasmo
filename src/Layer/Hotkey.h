#pragma once
#include "pch.h"
#include "Icetrix/Application.h"
#include "Icetrix/Events.h"
#include "Events.h"
#include "ImHotkey.h"
#include "Game.h"

class Hotkey
{
public:
	Hotkey()
	{
        g_sApp.dispatcher.sink<Icetrix::Layer::MenuDefaultWindowEvent>().connect<&Hotkey::Editor>(*this);
	}

	void Editor()
	{
        if (ImGui::Button("Edit Hotkeys"))
        {
            ImGui::OpenPopup("HotKeys Editor");
        }
        ImHotKey::Edit(hotkeys.data(), hotkeys.size(), "HotKeys Editor");
	}
};