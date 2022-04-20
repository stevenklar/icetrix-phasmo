#pragma once
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#include <appdata/pch-il2cpp.h>
#define WIN32_LEAN_AND_MEAN
#include "appdata/il2cpp-init.h"

// Defines
#define TRY(a) __try { a; } __except(EXCEPTION_EXECUTE_HANDLER) {}
#define SAVE_INSTANCE(a) g_mono(#a) = (a ## __TypeInfo) ? a ## __TypeInfo->static_fields->instance : nullptr;
#define SAVE_SINGLETON(a) g_mono(#a) = (a ## __TypeInfo) ? a ## __TypeInfo->static_fields->singleton : nullptr;

#define RESOLVE_FUNC(a, b, c, d, e) typedef b(__stdcall* f ## a) ## c; \
    f##a a = reinterpret_cast<f##a>(Icetrix::Memory::PatternScan::find_pattern_module("GameAssembly.dll", d, e))

#define RESOLVE_FUNCO(a, b, c, d, e, o) typedef b(__stdcall* f ## a) ## c; \
    f##a a = reinterpret_cast<f##a>(Icetrix::Memory::PatternScan::find_pattern_module("GameAssembly.dll", d, e) + o)

// Windows Header Files
#include <Windows.h>

// Std Header Files
#include <iostream>
#include <array>
#include <cstdint>
#include <vector>
#include <tlhelp32.h>
#include <Psapi.h>
#include <thread>
#include <codecvt>

// Custom Header Files
#include <Icetrix.h>
#include <Game.h>

// Hook
#include "Hook/AntiCheat.h"
#include "Hook/GameFunctions.h"
#include "Hook/Journal.h"

// Layer
#include "Layer/Debug.h"
#include "Layer/Ghost.h"
#include "Layer/ESP.h"
#include "Layer/GameVersion.h"
#include "Layer/UnlockCursor.h"
#include "Layer/ForceHost.h"
#include "Layer/ActivityMonitor.h"
#include "Layer/MissionCompleter.h"
#include "Layer/GhostAction.h"
#include "Layer/Speedhack.h"
#include "Layer/Hotkey.h"
#include "Layer/NoWatermark.h"
#include "Layer/Fly.h"
#include "Layer/Stamina.h"
