#pragma once

namespace options {
	namespace move {
		inline bool bhop = false;
	}

	namespace legit {
		inline bool backtrack = false;
		inline bool fake_latency = false;
	}

	namespace esp {
		inline bool box = false;
		inline color box_color = color(255, 255, 255, 255);
	}

	namespace chams {
		inline bool on = false;
		inline bool xqz = false;
		inline color visible = color(0, 250, 154, 255);
		inline color invisible = color(70, 130, 180, 255);
	}

	namespace misc {
		inline bool watermark = true;
		inline color watermark_color = color(55, 152, 237, 255);
	}
}