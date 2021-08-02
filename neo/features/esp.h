#pragma once
#include "../csgo/globals.h"

namespace esp {
	class player_ {
	public:
		bool begin(player_t* pl);
		void box(entity_t* ent);
	};
	void draw_list();
}