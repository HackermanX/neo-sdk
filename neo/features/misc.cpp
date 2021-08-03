#include "misc.h"

void miscfeatures::watermark() {
	if (!options::misc::watermark) return;

	render::draw_text("neo-sdk", { 10, 10 }, options::misc::watermark_color);
}