#include "esp.h"
#include "../csgo/misc/options.h"
#include "../rendering/imgui/imgui.h"
#include "lag_compensation.h"

namespace esp {
	RECT get_bounding_box(entity_t* ent) {
		RECT rect{};
		auto collideable = ent->get_collideable();
		if (!collideable)
			return rect;
		auto min = collideable->obb_mins();
		auto max = collideable->obb_maxs();
		const matrix3x4_t& trans = ent->coordinate_frame();
		vec3_t points[] = {
			vec3_t(min.x, min.y, min.z),
			vec3_t(min.x, max.y, min.z),
			vec3_t(max.x, max.y, min.z),
			vec3_t(max.x, min.y, min.z),
			vec3_t(max.x, max.y, max.z),
			vec3_t(min.x, max.y, max.z),
			vec3_t(min.x, min.y, max.z),
			vec3_t(max.x, min.y, max.z)
		};
		vec3_t points_transformed[8];
		for (int i = 0; i < 8; i++) {
			math::vector_transform(points[i], trans, points_transformed[i]);
		}
		vec3_t screen_points[8] = {};
		for (int i = 0; i < 8; i++) {
			if (!math::w2s(points_transformed[i], screen_points[i]))
				return rect;
		}
		auto left = screen_points[0].x;
		auto top = screen_points[0].y;
		auto right = screen_points[0].x;
		auto bottom = screen_points[0].y;
		for (int i = 1; i < 8; i++) {
			if (left > screen_points[i].x)
				left = screen_points[i].x;
			if (top < screen_points[i].y)
				top = screen_points[i].y;
			if (right < screen_points[i].x)
				right = screen_points[i].x;
			if (bottom > screen_points[i].y)
				bottom = screen_points[i].y;
		}
		return RECT{ (long)left, (long)top, (long)right, (long)bottom };
	}

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

	void draw_box(float x1, float y1, float x2, float y2, color clr, float size) {
		g::draw_list->AddLine(ImVec2(x1, y1), ImVec2(x2, y1), utils::to_im32(clr, clr.a()), size);
		g::draw_list->AddLine(ImVec2(x1, y2), ImVec2(x2, y2), utils::to_im32(clr, clr.a()), size);
		g::draw_list->AddLine(ImVec2(x1, y1), ImVec2(x1, y2), utils::to_im32(clr, clr.a()), size);
		g::draw_list->AddLine(ImVec2(x2, y1), ImVec2(x2, y2 + 1), utils::to_im32(clr, clr.a()), size);
	}

	void player_::box(entity_t* ent) {
		auto box = get_bounding_box(ent);
		draw_box(box.left, box.top, box.right, box.bottom, options::esp::box_color, 1.f);
	}
}