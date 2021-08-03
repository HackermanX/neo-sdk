#include "../hooks.h"

void __fastcall hooks::override_view::hook(void* _this, int edx, c_view_setup* view) {
	if (!csgo::engine->is_connected() || !csgo::engine->is_ingame())
		return original(csgo::client_mode, edx, view);

	if (!g::v_matrix::has_offset)
	{
		g::v_matrix::has_offset = true;
		g::v_matrix::offset = (reinterpret_cast<DWORD>(&csgo::engine->w2s_m()) + 0x40);
	}

	original(csgo::client_mode, edx, view);
}