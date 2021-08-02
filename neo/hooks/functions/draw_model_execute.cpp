#include "../hooks.h"
#include "../../features/chams.h"

void __stdcall hooks::draw_model_execute_hk(i_mat_render_context* context, const draw_model_state_t& state, const model_render_info_t& info, matrix3x4_t* bone) {
	static auto original = draw_model_execute.get_original<original_dme>();

	if (csgo::model_render->is_forced_material_override() && !strstr(info.model->name, "arms") && !strstr(info.model->name, "weapons/v"))
		return original(csgo::model_render, context, &state, &info, bone);

	chams::on_dme(context, state, info, bone);

	original(csgo::model_render, context, &state, &info, bone);

	csgo::model_render->forced_material_override(nullptr);
}