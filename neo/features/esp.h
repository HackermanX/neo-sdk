#pragma once
#include "../csgo/globals.h"

namespace esp {
	class player_ {
	public:
		struct {
			player_t*     player;
			bool          is_enemy;
			bool          is_visible;
			vec3_t        head_pos;
			vec3_t        feet_pos;
		} ctx;
		bool begin(player_t* pl);
		void box(entity_t* ent);
	};
	void draw_list();
}