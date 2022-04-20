#pragma once
#include "pch.h"
#include "Icetrix/Application.h"
#include "Icetrix/Events.h"
#include <appdata/helpers.h>
#include <appdata/pch-il2cpp.h>
#include "Utility.h"
#include "Game.h"
#include <iostream>
#include <fstream>

using namespace app;

class Fullbright
{
public:
    Fullbright()
    {
        g_sApp.dispatcher.sink<Icetrix::LayerEvent::Update>().connect<&Fullbright::Update>(*this);
        g_sApp.dispatcher.sink<Icetrix::LayerEvent::Attach>().connect<&Fullbright::Attach>(*this);
        g_sApp.dispatcher.sink<Icetrix::LayerEvent::Detach>().connect<&Fullbright::Detach>(*this);
		g_sApp.dispatcher.sink<Phasmo::Event::PlayerUpdate>().connect<&Fullbright::PlayerUpdate>(*this);
    }

	Phasmo::Player_1* localPlayer = nullptr;
    Icetrix::Feature* feature = new Icetrix::Feature{ "Fullbright", false };
    void Attach() { g_sFeatures->Push(feature); }
    void Detach() { delete feature; }
	void PlayerUpdate(Phasmo::Event::PlayerUpdate e) { this->localPlayer = e.localPlayer; }

    void Update()
    {
		if (!this->localPlayer)
			return;

		Phasmo::Animator* anim = localPlayer->fields.charAnim;
		auto boneTransform = Animator_GetBoneTransform((app::Animator*)anim, HumanBodyBones__Enum_Head, NULL);

		if (!boneTransform)
			return;

		//auto l = new Light();
		//Light* light = (Light*)Component_GetComponent((app::Component_1*)boneTransform, (app::Type)Light, NULL);

		//if (!light)
		if (true)
		{
			//light = boneTransform.gameObject.AddComponent<Light>();

			/*
			light.color = Color.white;
			light.type = LightType.Spot;
			light.shadows = LightShadows.None;
			light.range = 99f;
			light.spotAngle = 9999f;
			light.intensity = 0.3f;
			*/
		}
		else
		{
			//Object.Destroy(light);
		}
    }
};

