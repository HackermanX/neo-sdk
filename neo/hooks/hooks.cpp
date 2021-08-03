#include "hooks.h"
#include <stdexcept>

namespace hooks {
	void init() {
		steam::hook<create_move>(get_vfunc(csgo::client_mode, 24));

		steam::hook<end_scene>(get_vfunc(csgo::d3_device, 42));

		steam::hook<override_view>(get_vfunc(csgo::client_mode, 18));

		steam::hook<frame_stage_notify>(get_vfunc(csgo::client, 37));

		steam::hook<lock_cursor>(get_vfunc(csgo::surface, 67));

		steam::hook<draw_model_execute>(get_vfunc(csgo::model_render, 21));

		steam::hook<send_datagram>(utils::pattern_scan("engine.dll", "55 8B EC 83 E4 F0 B8 ? ? ? ? E8 ? ? ? ? 56 57 8B F9 89 7C 24 18")); //thanks tyler
	}
}