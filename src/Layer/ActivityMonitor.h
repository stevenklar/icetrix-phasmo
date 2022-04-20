#pragma once

#include "Icetrix/Application.h"
#include "Icetrix/Events.h"
#include <appdata/pch-il2cpp.h>
#include <imgui_internal.h>
#include "../../../../vendor/implot/implot.h"
#include "Utility.h"

#define MyFuncHook(a) \
		if (checkStatus(#a, MH_CreateHook(a, &h ## a, reinterpret_cast<LPVOID*>(&o ## a)))) \
			checkStatus(#a, MH_EnableHook(a));

#define MyDeFuncHook(a) \
		checkStatus(#a, MH_DisableHook(a));

class ActivityMonitor
{
private:
	Phasmo::GhostAI* ghost = nullptr;

	//typedef app::Vector3(__stdcall* fLineRenderer_GetPosition)(app::LineRenderer*, int32_t, MethodInfo);
	/*
	fLineRenderer_GetPosition* LineRenderer_GetPosition;
	uintptr_t pLineRenderer_GetPosition = Icetrix::Memory::PatternScan::find_pattern_module("GameAssembly.dll",
			"\x48\x89\x5C\x24\x08\x48\x89\x74\x24\x10\x57\x48\x83\xEC\x30\x33\xC0\x41\x8B\xF8\x48\x89\x44\x24\x20\x48\x8B\xF2\x89",
			"xxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
			*/

public:
	inline static float xs[60];
	inline static float ys[60];

	ActivityMonitor()
	{
        g_sApp.dispatcher.sink<Icetrix::LayerEvent::Attach>().connect<&ActivityMonitor::AttachFeature>(*this);
        g_sApp.dispatcher.sink<Icetrix::LayerEvent::Detach>().connect<&ActivityMonitor::DetachFeature>(*this);
        g_sApp.dispatcher.sink<Icetrix::LayerEvent::Attach>().connect<&ActivityMonitor::AttachHook>(*this);
        g_sApp.dispatcher.sink<Icetrix::LayerEvent::Detach>().connect<&ActivityMonitor::DetachHook>(*this);
		g_sApp.dispatcher.sink<Icetrix::Hook::InputEvent::afterInitialize>().connect<&ActivityMonitor::Initialize>(*this);
		g_sApp.dispatcher.sink<Icetrix::Hook::PresentEvent::Unhook>().connect<&ActivityMonitor::Shutdown>(*this);
		g_sApp.dispatcher.sink<Icetrix::Layer::MenuDrawEvent>().connect<&ActivityMonitor::Render>(*this);

		g_sApp.dispatcher.sink<Phasmo::Event::GhostUpdate>().connect<&ActivityMonitor::GhostUpdate>(*this);
		g_sApp.dispatcher.sink<Phasmo::Event::MainManagerUpdate>().connect<&ActivityMonitor::GarbageCollect>(*this);
	}

	Icetrix::Feature* feature = new Icetrix::Feature{ "Activity Monitor", false };
	void AttachFeature() { g_sFeatures->Push(feature); }
	void DetachFeature() { delete feature; }
	void GhostUpdate(Phasmo::Event::GhostUpdate e) { this->ghost = e.ghost; }
	void GarbageCollect() { this->ghost = nullptr; }

	void AttachHook()
	{
		/*
		if (!LineRenderer_GetPosition)
		{
			LOG_INFO("[Hook::LineRenderer_GetPosition] @ Failed");
			return;
		}
		*/

		//LineRenderer_GetPosition = reinterpret_cast<fLineRenderer_GetPosition*>(pLineRenderer_GetPosition);
		MyFuncHook(LineRenderer_GetPosition);
	}

	void DetachHook()
	{
		if (!LineRenderer_GetPosition)
			return;

		MyDeFuncHook(LineRenderer_GetPosition);
	}

	void Initialize() { ImPlot::CreateContext(); }
	void Shutdown() { ImPlot::DestroyContext(); }

	//DO_APP_FUNC(0x0170CA60, Vector3, LineRenderer_GetPosition, (LineRenderer* __this, int32_t index, MethodInfo* method));
	HOOK_DEF(app::Vector3, LineRenderer_GetPosition, (app::LineRenderer* __this, int32_t index, MethodInfo* method))
	{
		app::Vector3 pos = oLineRenderer_GetPosition(__this, index, method);
		xs[index] = (float)index;
		ys[index] = pos.y / 50;

		//LOG_INFO("[Hook::LineRenderer_GetPosition] " << std::hex << __this << " | INDEX: " << index);
		return oLineRenderer_GetPosition(__this, index, method);
	}

	void Render()
	{
		if (!feature->enabled)
			return;

		if (!ghost)
			return;

		if (!xs[59])
			return;

		bool enabled = feature->enabled;
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });
		ImGui::PushStyleColor(ImGuiCol_WindowBg, { 0.0f, 0.0f, 0.0f, 0.0f });
		if (ImGui::Begin("##ActivityMonitor", &enabled, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoNav))
		{
			ImPlot::SetNextPlotLimits(0, 60, 0, 10, ImGuiCond_Always);
			if (ImPlot::BeginPlot("##Activity", 0, 0, ImVec2(-1, 0), ImPlotFlags_NoHighlight | ImPlotFlags_AntiAliased | ImPlotFlags_NoBoxSelect | ImPlotFlags_NoMousePos | ImPlotFlags_NoLegend | ImPlotFlags_NoMenus))
			{
				ImPlot::PlotStairs("EMF", xs, ys, 60);
				ImPlot::EndPlot();
			}
			ImGui::End();
		}
		ImGui::PopStyleColor();
		ImGui::PopStyleVar(2);
	}
};
