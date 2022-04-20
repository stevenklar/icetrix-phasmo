// Generated C++ file by Il2CppInspector - http://www.djkaty.com - https://github.com/djkaty
// IL2CPP application initializer

#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "il2cpp-init.h"
#include "helpers.h"
#include "Icetrix/Memory/PatternScan.h"

#define DO_API(r, n, p) r (*n) p
#include "il2cpp-api-functions.h"
#undef DO_API

// Application-specific functions
#define DO_GAME_FUNC(r, n, p, x, y) r (*n) p
#define DO_APP_FUNC(a, r, n, p) r (*n) p
#define DO_FUNC(r, n, p, s) r (*n) p
namespace app {
	#include "il2cpp-functions.h"
}
#undef DO_FUNC
#undef DO_APP_FUNC
#undef DO_GAME_FUNC

// TypeInfo pointers
#define DO_CLASS(n, s) n ## __Class* n ## __TypeInfo
#define DO_TYPEDEF(a, n) n ## __Class* n ## __TypeInfo
namespace app {
#include "il2cpp-types-ptr.h"
}
#undef DO_TYPEDEF
#undef DO_CLASS

// IL2CPP application initializer
void init_il2cpp()
{
	// Get base address of IL2CPP module
	uintptr_t baseAddress = GetBaseAddress();
	HMODULE moduleHandle = GetModuleHandleW(L"GameAssembly.dll");

	#define DO_API(r, n, p) n = (r (*) p)(GetProcAddress(moduleHandle, #n))
	#include "il2cpp-api-functions.h"
	#undef DO_API

	// Define IL2CPP API function addresses
	/*
	#define DO_API(r, n, p) n = (r (*) p)(baseAddress + n ## _ptr)
	#include "il2cpp-api-functions.h"
	#undef DO_API
	*/

	using namespace app;

	// Define function addresses
	#define DO_APP_FUNC(a, r, n, p) n = (r (*) p)(baseAddress + a)
	#define DO_GAME_FUNC(r, n, p, x, y) uintptr_t jmp_##n = Icetrix::Memory::PatternScan::find_pattern_module("GameAssembly.dll", x, y); \
		if (jmp_##n) { n = (r (*) p)(jmp_##n + 0x5 + *reinterpret_cast<std::int32_t*>(jmp_##n + 0x1)); } \
		LOG_INFO("[PatternScan::" << #n << "] @ " << std::hex << n)
	#define DO_FUNC(r, n, p, s) n = reinterpret_cast<decltype(n)>(get_method(s)); \
		LOG_INFO("[AutoSearch::" << #n << "] @ " << std::hex << n)
	#include "il2cpp-functions.h"
	#undef DO_FUNC
	#undef DO_GAME_FUNC
	#undef DO_APP_FUNC

	// Define TypeInfo variables
	#define DO_CLASS(n, s) n ## __TypeInfo = reinterpret_cast<decltype(n ## __TypeInfo)>(get_class(s))
	#define DO_TYPEDEF(a, n) n ## __TypeInfo = *(n ## __Class**) (baseAddress + a);
	#include "il2cpp-types-ptr.h"
	#undef DO_TYPEDEF
	#undef DO_CLASS
}