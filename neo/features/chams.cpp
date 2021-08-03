#include "chams.h"
#include "../hooks/hooks.h"
#include "../csgo/misc/options.h"

namespace chams {
	void override_material(int mat /*just incase we want to add multiple mats laiter*/, bool ignorez, const color& rgba) {
		i_material* material = nullptr;

		switch (mat)
		{
		case 1:
			material = csgo::material_system->find_material(xor("debug/debugambientcube"), TEXTURE_GROUP_MODEL);
			break;
		}

		material->color_modulate(rgba.r() / 255.0f, rgba.g() / 255.0f, rgba.b() / 255.0f);
		material->alpha_modulate(rgba.a() / 255.0f);
		material->set_material_var_flag(MATERIAL_VAR_IGNOREZ, ignorez);

		csgo::model_render->forced_material_override(material);
	}

	void on_dme(i_mat_render_context* ctx, const draw_model_state_t& state, const model_render_info_t& info, matrix3x4_t* bone) {
		player_t* player = player_t::get_player_by_index(info.entity_index);

		if (info.entity_index > 0 && info.entity_index <= 64) {

			if (player && g::local) {

				if (player->team() != g::local->team()) {

					const auto color_front = options::chams::visible;
					const auto color_back = options::chams::invisible;

					if (options::chams::on) {
						if (options::chams::xqz) {
							override_material(1, true, color_back);
							hooks::draw_model_execute::original(csgo::model_render, 0, ctx, state, info, bone);
							override_material(1, false, color_front);
						}
						else {
							override_material(1, false, color_front);
						}
					}
				}
			}
		}
	}
}