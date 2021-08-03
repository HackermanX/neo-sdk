#include "../hooks.h"
#include "../../features/chams.h"

void __fastcall hooks::draw_model_execute::hook(void* thisptr, int edx, i_mat_render_context* context, const draw_model_state_t& state, const model_render_info_t& info, matrix3x4_t* bone) {

	if (csgo::model_render->is_forced_material_override() && !strstr(info.model->name, "arms") && !strstr(info.model->name, "weapons/v"))
		return original(thisptr, edx, context, state, info, bone);

	chams::on_dme(context, state, info, bone);

	original(thisptr, edx, context, state, info, bone);

	csgo::model_render->forced_material_override(nullptr);
}