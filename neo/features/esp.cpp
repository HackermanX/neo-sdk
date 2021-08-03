#include "esp.h"
#include "../csgo/misc/options.h"
#include "../rendering/render.h"

namespace esp {
	bool player_::begin(player_t* pl) {
		if (pl->is_dormant() || !pl->is_alive() || !g::local)
			return false;

		if (!(g::local->team() != pl->team()))
			return false;

		return true;
	}

	void draw_list() {
		auto player = player_();
		for (auto i = 1; i <= csgo::entity_list->get_highest_entity_index(); ++i) {
			auto entity = entity_t::get_entity_by_index(i);
			if (!entity) continue;

			if (i <= csgo::globals->max_clients) {
				if (player.begin((player_t*)entity)) {
					if (options::esp::box) player.box(entity);
				}
			}
		}
	}

	void player_::box(entity_t* ent) {
		auto box = render::get().get_bounding_box(ent);
		render::get().draw_box(box.left, box.top, box.right, box.bottom, options::esp::box_color, 1.f);
	}
}