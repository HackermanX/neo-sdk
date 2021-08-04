#pragma once
#include "../csgo/globals.h"

namespace esp {
	class player_ {
	public:
		bool begin(player_t* pl);
		void box(entity_t* ent);
		void health(entity_t* ent);
		void weapon(entity_t* ent);
		void ammo(entity_t* ent);
		void scoped(entity_t* ent);

		int bottom_spacing_y;

		int top_spacing_y;
	};
	void draw_list();
}