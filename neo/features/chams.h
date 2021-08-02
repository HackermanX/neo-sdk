#pragma once
#include "../csgo/globals.h"

namespace chams {
	void override_material(int mat, bool ignorez, const color& rgba);
	void on_dme(i_mat_render_context* ctx, const draw_model_state_t& state, const model_render_info_t& info, matrix3x4_t* bone);
}