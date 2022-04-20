#pragma once

#include "Icetrix/Renderer.h"
#include "Icetrix/Layer.h"
#include "Icetrix/Events.h"
#include "Icetrix/Hook/DxgiSwapChainPresent.h"

class NoWatermark
{
public:
	NoWatermark()
	{
		g_sApp.dispatcher.sink<Icetrix::Layer::MenuInitEvent>().connect<&NoWatermark::Init>(*this);
	}

	void Init()
	{
		g_sRenderer->Initialize(false);
	}
};
