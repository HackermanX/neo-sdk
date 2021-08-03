#include "../hooks.h"
#include "../../rendering/menu.h"

void __fastcall hooks::lock_cursor::hook(void* _this) {
	if (menu::is_visible()) {
		csgo::surface->unlock_cursor();
		csgo::input->reset_input_state();
		return;
	}
	original(csgo::surface);
}