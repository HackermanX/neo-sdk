#pragma once
#include "../rendering/imgui/imgui.h"
#include "../features/lag_compensation.h"

namespace render {
	RECT get_bounding_box(entity_t* ent);
	void draw_box(float x1, float y1, float x2, float y2, color clr, float size);
	void draw_text(std::string text, ImVec2 position, color color);
};