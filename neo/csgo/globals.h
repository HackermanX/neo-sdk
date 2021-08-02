#pragma once
#include "classes/entities.h"
#include "../rendering/imgui/imgui.h"

namespace g {
	extern player_t* local;
	extern ImDrawList* draw_list;
	namespace v_matrix {
		extern bool has_offset;
		extern DWORD offset;
	}
}