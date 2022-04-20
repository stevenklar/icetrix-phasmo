#pragma once
#include "Icetrix/Application.h"
#include "Icetrix/Events.h"
#include "Events.h"
#include <appdata/pch-il2cpp.h>
#include <imgui_internal.h>

class Speedhack
{
private:
	float fov = 80.f;
	float timeScale = 1.f;
	float gravity = 1.f;
	float runstep = 1.f;
	float stepCycle = 1.f;
	float stepInterval = 1.f;
public:
	Speedhack()
	{
		g_sApp.dispatcher.sink<Icetrix::LayerEvent::Attach>().connect<&Speedhack::Attach>(*this);
		g_sApp.dispatcher.sink<Icetrix::LayerEvent::Detach>().connect<&Speedhack::Detach>(*this);
        g_sApp.dispatcher.sink<Icetrix::Layer::MenuDefaultWindowEvent>().connect<&Speedhack::Render>(*this);
		g_sApp.dispatcher.sink<Phasmo::Event::TimeScale>().connect<&Speedhack::Update>(*this);
		g_sApp.dispatcher.sink<Phasmo::Event::FirstPersonControllerUpdate>().connect<&Speedhack::UpdateFps>(*this);
		g_sApp.dispatcher.sink<Icetrix::LayerEvent::Detach>().connect<&Speedhack::Reset>(*this);
	}

	static inline Icetrix::Feature* feature = new Icetrix::Feature{ "Speedhack", false };
	void Attach() { g_sFeatures->Push(feature); }
	void Detach() { delete feature; }

	void Render()
	{
		if (!feature->enabled)
			return;

		ImGui::SliderFloat("Fov", &fov, 1, 200);
		ImGui::SliderFloat("Game Speed", &timeScale, 1, 10);
		ImGui::SliderFloat("Gravity Multiplier", &gravity, 0, 100);
		ImGui::SliderFloat("Runstep Length", &runstep, 0, 100);
		ImGui::SliderFloat("Step Cycle", &stepCycle, 0, 100);
		ImGui::SliderFloat("Step Interval", &stepInterval, 0, 100);
	}

	void Update(Phasmo::Event::TimeScale e)
	{
		if (!feature->enabled)
			return;

		*(e.timeScale) = timeScale;

		// test camera
		auto camera = app::Camera_get_main(NULL);
		app::Camera_set_fieldOfView(camera, fov, NULL);
	}

	void UpdateFps(Phasmo::Event::FirstPersonControllerUpdate e)
	{
		if (!feature->enabled)
		{
			stepInterval = e.firstPersonController->fields.m_StepInterval;
			stepCycle = e.firstPersonController->fields.m_StepCycle;
			return;
		}

		e.firstPersonController->fields.m_StepInterval = stepInterval;
		e.firstPersonController->fields.m_StepCycle = stepCycle;
	}

	void Reset()
	{
		Time_set_timeScale(1.f, NULL);
	}
};
