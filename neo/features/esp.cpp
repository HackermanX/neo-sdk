#include "esp.h"
#include "../csgo/misc/options.h"
#include "../rendering/render.h"

bool esp::player_::begin(player_t* pl) {
	if (pl->is_dormant() || !pl->is_alive() || !g::local)
		return false;

	if (!(g::local->team() != pl->team()))
		return false;

	return true;
}

void esp::draw_list() {
	auto player = player_();
	for (auto i = 1; i <= csgo::entity_list->get_highest_entity_index(); ++i) {
		auto entity = entity_t::get_entity_by_index(i);
		if (!entity) continue;

		if (i <= csgo::globals->max_clients) {
			if (player.begin((player_t*)entity)) {
				if (options::esp::box_esp) player.box(entity);

				if (options::esp::health_esp) player.health(entity);

				if (options::esp::weapon_esp) player.weapon(entity);

				if (options::esp::ammo_esp) player.ammo(entity);

				if (options::esp::scoped_esp) player.scoped(entity);
			}
		}
	}
}

void esp::player_::box(entity_t* ent) {
	auto box = render::get_bounding_box(ent);
	render::draw_box(box.left, box.top, box.right, box.bottom, options::esp::box_color, 1.f);
}

void esp::player_::weapon(entity_t* ent) {
	auto box = render::get_bounding_box(ent);

	std::string active_weapon = ent->active_weapon().get()->name();

	render::draw_text(active_weapon, ImVec2(box.right, box.top), options::esp::weapon_color);
	esp::player_::top_spacing_y += 10;
}

void esp::player_::ammo(entity_t* ent) {
	auto box = render::get_bounding_box(ent);

	std::string ammo = std::to_string(ent->active_weapon().get()->clip());

	render::draw_text(ammo, ImVec2(box.left, box.top + esp::player_::top_spacing_y), options::esp::ammo_color);
}

void esp::player_::health(entity_t* ent) {
	auto box = render::get_bounding_box(ent);

	std::string player_health = std::to_string(ent->health()) + "HP";

	render::draw_text(player_health, ImVec2(box.right + 5, box.bottom), options::esp::health_color);
	esp::player_::bottom_spacing_y += 10;
}

void esp::player_::scoped(entity_t* ent) {
	auto box = render::get_bounding_box(ent);

	bool scoped = false;

	if (ent->active_weapon().get()->zoom_level() > 0)
		scoped = true;
	else
		scoped = false;

	if (scoped)
		render::draw_text("scoped", ImVec2(box.right + 5, box.bottom + esp::player_::bottom_spacing_y), options::esp::scoped_color);
}