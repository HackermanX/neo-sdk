#pragma once
#include "../csgo/globals.h"
#include <intrin.h>
#include "../rendering/imgui/impl/imgui_impl_dx9.h"
#include "steam_hook.h"

namespace hooks {
	void init();

	inline constexpr void* get_vfunc(void* thisptr, std::size_t nIndex) {
		return (void*)((*(std::uintptr_t**)thisptr)[nIndex]);
	}

	declare_hook(draw_model_execute, void(__fastcall*)(void*, int, i_mat_render_context*, const draw_model_state_t&, const model_render_info_t&, matrix3x4_t*));
	declare_hook(create_move, bool(__fastcall*)(void*, int, float, c_cmd*));
	declare_hook(end_scene, long(__stdcall*)(IDirect3DDevice9*));
	declare_hook(override_view, void(__fastcall*)(void*, int, c_view_setup*));
	declare_hook(frame_stage_notify, void(__stdcall*)(frame_stage));
	declare_hook(lock_cursor, void(__fastcall*)(void*));
	declare_hook(send_datagram, int(__fastcall*)(i_net_channel*, int, bf_write*));
}