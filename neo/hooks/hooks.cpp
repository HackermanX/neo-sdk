#include "hooks.h"
#include <stdexcept>

namespace hooks {
	void init() {
		//initialize hooks
		if (MH_Initialize() != MH_OK)
			throw std::runtime_error("failed to initialize your shit cheat.");
		//create hooks

		if (!create_move.create(get_vfunc(csgo::client_mode, 24), &create_move_hk))
			throw std::runtime_error("failed to initialize create_move_hk");

		if (!end_scene.create(get_vfunc(csgo::d3_device, 42), &end_scene_hk))
			throw std::runtime_error("failed to initialize end_scene_hk");

		if (!override_view.create(get_vfunc(csgo::client_mode, 18), &override_view_hk))
			throw std::runtime_error("failed to initialize override_view_hk");

		if (!fsn.create(get_vfunc(csgo::client, 37), &fsn_hk))
			throw std::runtime_error("failed to initialize fsn_hk");

		if (!lock_cursor.create(get_vfunc(csgo::surface, 67), &lock_cursor_hk))
			throw std::runtime_error("failed to initialize lock_cursor_hk");

		if (!draw_model_execute.create(get_vfunc(csgo::model_render, 21), &draw_model_execute_hk))
			throw std::runtime_error("failed to initialize draw_model_execute_hk");
	}
}
