#include <windows.h>
#include <cstdint>
#include "csgo/sdk.h"
#include "hooks/hooks.h"
#include "rendering/menu.h"
#include "csgo/misc/input.h"

void hotkeys(LPVOID base) {
	input_system::register_hotkey(VK_INSERT, []()
		{
			menu::toggle();
		});
}

unsigned long __stdcall on_attach(void* base) {
	utils::attach_console(); //can make attach only in debug now ig but it was usefull in release at first too
	csgo::init();
	csgo::dump();
	netvars.init();
	input_system::initialize();
	menu::init();
	hooks::init();
	hotkeys(base);

	utils::console_print("attached! enjoy neo-sdk.\n");
	utils::console_print("built on: %s %s\n", __DATE__, __TIME__);
	return true;
}

bool __stdcall DllMain(void* base, uint32_t reason_to_call, void* reserved) {
	if (reason_to_call == DLL_PROCESS_ATTACH)
		CreateThread(nullptr, 0, static_cast<LPTHREAD_START_ROUTINE>(on_attach), reserved, 0, nullptr);
	return TRUE;
}