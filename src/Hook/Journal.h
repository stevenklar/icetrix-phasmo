#pragma once
#include "Icetrix/Application.h"
#include "Icetrix/Events.h"
#include "Events.h"
#include "examples/imgui_impl_win32.h"

IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

class Journal
{
private:
	Phasmo::JournalController* journalController = nullptr;
public:
	Journal()
	{
		g_sApp.dispatcher.sink<Icetrix::Hook::InputEvent::hwndProc>().connect<&Journal::Input>(*this);
		g_sApp.dispatcher.sink<Phasmo::Event::JournalControllerUpdate>().connect<&Journal::JournalControllerUpdate>(*this);
		g_sApp.dispatcher.sink<Phasmo::Event::SceneManagerLoadScene>().connect<&Journal::GarbageCollect>(*this);
		g_sApp.dispatcher.sink<Phasmo::Event::GameControllerExit>().connect<&Journal::GarbageCollect>(*this);
		g_sApp.dispatcher.sink<Phasmo::Event::RewardManagerAwake>().connect<&Journal::GarbageCollect>(*this);
	}

	void JournalControllerUpdate(Phasmo::Event::JournalControllerUpdate e) { this->journalController = (Phasmo::JournalController*)e.journalController; }
	void GarbageCollect() { this->journalController = nullptr; }

	void Input(const Icetrix::Hook::InputEvent::hwndProc& input)
	{
		if (journalController != nullptr && journalController->fields.isOpen)
			ImGui_ImplWin32_WndProcHandler(input.hWnd, input.uMsg, input.wParam, input.lParam);
	}
};
