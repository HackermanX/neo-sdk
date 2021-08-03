#pragma once
#include "../csgo/globals.h"
#include "minhook/detour.h"
#include <intrin.h>
#include "../rendering/imgui/impl/imgui_impl_dx9.h"
#include <d3d9.h>

namespace hooks {
	inline detour_hook create_move;
	inline detour_hook end_scene;
	inline detour_hook override_view;
	inline detour_hook fsn;
	inline detour_hook send_datagram;
	inline detour_hook lock_cursor;
	inline detour_hook draw_model_execute;

	using original_dme = void(__thiscall*)(iv_model_render*, i_mat_render_context*, const draw_model_state_t*, const model_render_info_t*, matrix3x4_t*);

	void init();
	inline constexpr void* get_vfunc(void* thisptr, std::size_t nIndex) {
		return (void*)((*(std::uintptr_t**)thisptr)[nIndex]);
	}
	bool __fastcall create_move_hk(void* thisptr, int edx, float fl_input_sample_time, c_cmd* cmd);
	long __stdcall end_scene_hk(IDirect3DDevice9* pDevice);
	void __fastcall override_view_hk(void* _this, int edx, c_view_setup* view);
	void __stdcall fsn_hk(frame_stage stage);
	int __fastcall send_datagram_hk(i_net_channel* thisptr, int edx, bf_write* datagram);
	void __fastcall lock_cursor_hk(void* _this);
	void __stdcall draw_model_execute_hk(i_mat_render_context* context, const draw_model_state_t& state, const model_render_info_t& info, matrix3x4_t* bone);
}