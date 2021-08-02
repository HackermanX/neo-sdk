#include "../hooks.h"
#include "../../rendering/menu.h"

void __fastcall hooks::lock_cursor_hk(void* _this) {
	static auto original = lock_cursor.get_original<decltype(&lock_cursor_hk)>();
	if (menu::is_visible()) {
		csgo::surface->unlock_cursor();
		csgo::input->reset_input_state();
		return;
	}
	original(csgo::surface);
}