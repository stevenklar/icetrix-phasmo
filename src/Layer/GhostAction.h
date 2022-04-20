#pragma once

#include "Icetrix/Application.h"
#include "Icetrix/Events.h"
#include <appdata/pch-il2cpp.h>
#include <Game.h>
#include <Utility.h>

static app::Object__Array* oObjectArray;
static app::Boolean__Boxed* oBool;

class GhostAction
{
private:
	Phasmo::GhostAI* ghost = nullptr;
public:
	GhostAction()
    {
        g_sApp.dispatcher.sink<Icetrix::LayerEvent::Attach>().connect<&GhostAction::Attach>(*this);
        g_sApp.dispatcher.sink<Icetrix::LayerEvent::Detach>().connect<&GhostAction::Detach>(*this);
        g_sApp.dispatcher.sink<Icetrix::Layer::MenuDrawEvent>().connect<&GhostAction::Render>(*this);
        g_sApp.dispatcher.sink<Phasmo::Event::GhostUpdate>().connect<&GhostAction::Update>(*this);
        g_sApp.dispatcher.sink<Phasmo::Event::GhostUpdate>().connect<&GhostAction::GhostUpdate>(*this);
        g_sApp.dispatcher.sink<Phasmo::Event::MainManagerUpdate>().connect<&GhostAction::GarbageCollect>(*this);
		g_sApp.dispatcher.sink<Phasmo::Event::SceneManagerLoadScene>().connect<&GhostAction::GarbageCollect>(*this);
		g_sApp.dispatcher.sink<Phasmo::Event::GameControllerExit>().connect<&GhostAction::GarbageCollect>(*this);
		g_sApp.dispatcher.sink<Phasmo::Event::RewardManagerAwake>().connect<&GhostAction::GarbageCollect>(*this);
    }

    Icetrix::Feature* feature = new Icetrix::Feature{ "Ghost Actions", true };

    void Attach() { g_sFeatures->Push(feature); }
    void Detach() { delete feature; }
	void GhostUpdate(Phasmo::Event::GhostUpdate e) { this->ghost = e.ghost; }
    void GarbageCollect() { this->ghost = nullptr; }

    void Render()
    {
        if (!feature->enabled)
            return;

        if (!ghost)
            return;

        bool enabled = feature->enabled;
        if (ImGui::Begin("Actions", &enabled, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse))
        {
            if (ImGui::Button("Start Hunting"))
                g_mono("force_hunt") = true;

            if (ImGui::Button("Stop Hunting"))
                g_mono("force_unhunt") = true;

            if (ImGui::Button("Idle"))
                g_mono("force_idle") = true;

            if (ImGui::Button("Wander"))
                g_mono("force_wander") = true;

            if (ImGui::Button("Appear"))
                g_mono("force_appear") = true;

            if (ImGui::Button("UnAppear"))
                g_mono("force_unappear") = true;

            if (ImGui::Button("Door knock"))
                g_mono("force_doorknock") = true;

            if (ImGui::Button("Car alarm"))
                g_mono("force_caralarm") = true;

            if (ImGui::Button("Radio"))
                g_mono("force_radio") = true;

            if (ImGui::Button("Flicker"))
                g_mono("force_flicker") = true;

            if (ImGui::Button("Random"))
                g_mono("force_random") = true;
        }

		ImGui::End();
    }

    void Update(Phasmo::Event::GhostUpdate update)
    {
        if (g_mono("force_hunt"))
        {
            update.ghost->fields.isHunting = true;
            update.ghost->fields.canAttack = true;
            update.ghost->fields.canEnterHuntingMode = true;
            update.ghost->fields.ghostIsAppeared = true;
            //update.ghost->fields.isChasingPlayer = true;
            update.ghost->fields.canWander = true;
            update.ghost->fields.playerToKill = nullptr;
            //GhostAI_ChasingPlayer((app::GhostAI*)update.ghost, true, NULL);
			app::GhostAI_ChangeState((app::GhostAI*)update.ghost, (GhostAI___Enum)Phasmo::GhostAI_States__Enum::hunting, NULL, NULL, NULL);
            GhostAI_Hunting((app::GhostAI*)update.ghost, true, NULL);
			app::PhotonView_RPC((app::PhotonView*)update.ghost->fields.view, CreateNETStringFromANSI("Hunting"), (app::RpcTarget__Enum)Phasmo::RpcTarget__Enum::RpcTarget__Enum_All, NULL, NULL);
            g_mono("force_hunt") = false;
		}

        if (g_mono("force_unhunt"))
        {
            update.ghost->fields.isHunting = false;
			app::GhostAI_ChangeState((app::GhostAI*)update.ghost, (GhostAI___Enum)Phasmo::GhostAI_States__Enum::favouriteRoom, NULL, NULL, NULL);
			GhostAI_Hunting((app::GhostAI*)update.ghost, false, NULL);
            g_mono("force_unhunt") = false;
        }

        if (g_mono("force_idle"))
        {
			app::GhostAI_ChangeState((app::GhostAI*)update.ghost, (GhostAI___Enum)Phasmo::GhostAI_States__Enum::idle, NULL, NULL, NULL);
            g_mono("force_idle") = false;
        }

        if (g_mono("force_wander"))
        {
			app::GhostAI_ChangeState((app::GhostAI*)update.ghost, (GhostAI___Enum)Phasmo::GhostAI_States__Enum::wander, NULL, NULL, NULL);
            g_mono("force_wander") = false;
        }
        if (g_mono("force_appear"))
        {
			app::GhostAI_Appear((app::GhostAI*)update.ghost, true, NULL);
            g_mono("force_appear") = false;
        }
        if (g_mono("force_unappear"))
        {
			app::GhostAI_UnAppear((app::GhostAI*)update.ghost, false, NULL);
            g_mono("force_unappear") = false;
        }
        if (g_mono("force_doorknock"))
        {
			app::GhostAI_ChangeState((app::GhostAI*)update.ghost, (GhostAI___Enum)Phasmo::GhostAI_States__Enum::doorKnock, NULL, NULL, NULL);
            g_mono("force_doorknock") = false;
        }
        if (g_mono("force_caralarm"))
        {
			app::GhostAI_ChangeState((app::GhostAI*)update.ghost, (GhostAI___Enum)Phasmo::GhostAI_States__Enum::carAlarm, NULL, NULL, NULL);
            g_mono("force_caralarm") = false;
        }
        if (g_mono("force_radio"))
        {
			app::GhostAI_ChangeState((app::GhostAI*)update.ghost, (GhostAI___Enum)Phasmo::GhostAI_States__Enum::radio, NULL, NULL, NULL);
            g_mono("force_radio") = false;
        }
        if (g_mono("force_flicker"))
        {
			app::GhostAI_ChangeState((app::GhostAI*)update.ghost, (GhostAI___Enum)Phasmo::GhostAI_States__Enum::flicker, NULL, NULL, NULL);
            g_mono("force_flicker") = false;
        }
        if (g_mono("force_random"))
        {
			app::GhostAI_ChangeState((app::GhostAI*)update.ghost, (GhostAI___Enum)Phasmo::GhostAI_States__Enum::randomEvent, NULL, NULL, NULL);
            g_mono("force_random") = false;
        }
    }

};
