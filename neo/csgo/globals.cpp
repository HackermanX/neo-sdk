#include "globals.h"

namespace g {
	player_t* local = nullptr;
	ImDrawList* draw_list = nullptr;
	namespace v_matrix {
		bool has_offset = false;
		DWORD offset;
	}
}