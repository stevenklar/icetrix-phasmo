#pragma once
#include <pch.h>
#include "Icetrix/Application.h"
#include "Icetrix/Events.h"
#include "Events.h"
#include <appdata/pch-il2cpp.h>
#include <imgui_internal.h>
#include <appdata\helpers.h>
#include "../kiero/minhook/include/MinHook.h"
#include "Game.h"

class Debug
{
public:
	Phasmo::Player_1* localPlayer = nullptr;
	Phasmo::GhostAI* ghost = nullptr;
	app::OuijaBoard* ouijaBoard = nullptr;
	app::DNAEvidence* bone = nullptr;
	Phasmo::MainManager* mainManager = nullptr;
	Phasmo::MissionManager* missionManager = nullptr;
	Phasmo::JournalController* journalController = nullptr;

public:
	Debug()
	{
		g_sApp.dispatcher.sink<Icetrix::LayerEvent::Attach>().connect<&Debug::TestSignatures>(*this);

		g_sApp.dispatcher.sink<Icetrix::LayerEvent::Attach>().connect<&Debug::Attach>(*this);
		g_sApp.dispatcher.sink<Icetrix::LayerEvent::Detach>().connect<&Debug::Detach>(*this);
        g_sApp.dispatcher.sink<Icetrix::Layer::MenuDrawEvent>().connect<&Debug::Render>(*this);

		g_sApp.dispatcher.sink<Phasmo::Event::GhostUpdate>().connect<&Debug::GhostUpdate>(*this);
		g_sApp.dispatcher.sink<Phasmo::Event::OuijaBoardUpdate>().connect<&Debug::OuijaUpdate>(*this);
		g_sApp.dispatcher.sink<Phasmo::Event::DNAEvidenceUpdate>().connect<&Debug::BoneUpdate>(*this);
		g_sApp.dispatcher.sink<Phasmo::Event::PlayerUpdate>().connect<&Debug::PlayerUpdate>(*this);
		g_sApp.dispatcher.sink<Phasmo::Event::MissionManagerUpdate>().connect<&Debug::MissionManagerUpdate>(*this);
		g_sApp.dispatcher.sink<Phasmo::Event::MainManagerUpdate>().connect<&Debug::MainManagerUpdate>(*this);

		g_sApp.dispatcher.sink<Phasmo::Event::SceneManagerLoadScene>().connect<&Debug::LogScene>(*this);
		g_sApp.dispatcher.sink<Phasmo::Event::SceneManagerLoadScene>().connect<&Debug::GarbageCollect>(*this);
		g_sApp.dispatcher.sink<Phasmo::Event::GameControllerExit>().connect<&Debug::GarbageCollect>(*this);
		g_sApp.dispatcher.sink<Phasmo::Event::RewardManagerAwake>().connect<&Debug::GarbageCollect>(*this);
		g_sApp.dispatcher.sink<Phasmo::Event::JournalControllerUpdate>().connect<&Debug::JournalControllerUpdate>(*this);
	}

	static inline Icetrix::Feature* feature = new Icetrix::Feature{ "Debug Window", true };
	void Attach()
	{
		g_sFeatures->Push(feature);
	}
	void Detach() { delete feature; }

	void Render()
	{
		if (!feature->enabled)
			return;

		bool enabled = feature->enabled;
        if (ImGui::Begin("Debug", &enabled, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoCollapse))
        {
			ImGui::Text("Player: 0x%08x", localPlayer);
			ImGui::Text("JournalController: 0x%08x", journalController);
			if (journalController)
				ImGui::Text("Book is open: %s", (journalController->fields.isOpen) ? "Yes" : "No");
			ImGui::Spacing();
			ImGui::Text("GhostAI: 0x%08x", ghost);
			ImGui::Text("OuijaBoard: 0x%08x", ouijaBoard);
			ImGui::Text("Bone: 0x%08x", bone);
			ImGui::Spacing();
			ImGui::Text("MainManager: 0x%08x", mainManager);
			ImGui::Text("MissionManager: 0x%08x", missionManager);

            ImGui::End();
        }

		//if (localPlayer)
			//localPlayer->fields.charAnim
	}

	void GhostAwake(Phasmo::Event::GhostUpdate e) { this->ghost = e.ghost; }
	void GhostUpdate(Phasmo::Event::GhostUpdate e) { this->ghost = e.ghost; }
	void OuijaUpdate(Phasmo::Event::OuijaBoardUpdate e) { this->ouijaBoard = e.ouijaBoard; }
	void BoneUpdate(Phasmo::Event::DNAEvidenceUpdate e) { this->bone = e.bone; }
	void PlayerUpdate(Phasmo::Event::PlayerUpdate e) { this->localPlayer = e.localPlayer; }
	void MissionManagerUpdate(Phasmo::Event::MissionManagerUpdate e) { this->missionManager = e.missionManager; }
	void MainManagerUpdate(Phasmo::Event::MainManagerUpdate e) { this->mainManager = e.mainManager; }
	void JournalControllerUpdate(Phasmo::Event::JournalControllerUpdate e) { this->journalController = (Phasmo::JournalController*)e.journalController; }

	void LogScene(Phasmo::Event::SceneManagerLoadScene e)
	{
		LOG_INFO("[Debug::OnSceneManagerLoadScene] Scene: " << e.sceneName);
	}

	void GarbageCollect()
	{
		LOG_INFO("[Debug::GarbageCollect]");
		localPlayer = nullptr;
		ghost = nullptr;
		ouijaBoard = nullptr;
		bone = nullptr;
		mainManager = nullptr;
		missionManager = nullptr;
		journalController = nullptr;
	}

	void TestSignatures()
	{
		/*
		auto domain = il2cpp_domain_get();
		auto assembly = il2cpp_domain_assembly_open(domain, "Assembly-CSharp");
		auto klass = il2cpp_class_from_name(assembly->image, "", "GhostAI");
		output_class_methods(klass);
		*/
	}
};
