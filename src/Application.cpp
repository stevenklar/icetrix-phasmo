#include "pch.h"
#include "Icetrix/Entrypoint.h"

#define BUILD 1 // private=0 | public=1
#define OVERLAY 0 // no=0 yes=1		BUILD must be set to private=0
#undef KIERO_INCLUDE_OPENGL
#define KIERO_INCLUDE_OPENGL 0

void Icetrix::CreateApplication()
{
	new Icetrix::Layer::PanicKey;

#if (OVERLAY == 1)	// stream safe overlay only for private build
	new Icetrix::Hook::Graphic::Discord; // stream safe
#else
	new Icetrix::Hook::Graphic::Kiero; // non-stream safe
#endif

	new Icetrix::Hook::Input::Win32;

	// Default features
	new Icetrix::Layer::SimpleMenu(VK_DELETE);

	new NoWatermark;
	//new Icetrix::Layer::Watermark;

	// Game features
	new GameFunctions;
	new AntiCheat;
	new UnlockCursor;
	new Ghost;
	new ESP;
	new ActivityMonitor;
	new Journal;
	new MissionCompleter;
	new Speedhack;
	//new Fly;
	new Stamina;

#if (BUILD == 0)	// private
	new GameVersion;
	new ForceHost;
	new GhostAction;
	new Hotkey;
#endif

	new Icetrix::Layer::Crosshair;

	init_il2cpp();
	il2cpp_gc_disable();

#ifdef _DEBUG
	new Debug;
#endif
}
