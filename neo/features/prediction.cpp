#include "prediction.h"
#include "../csgo/sdk.h"

float prediction::prev_curtime;
float prediction::prev_frametime;

int tick_base;
c_cmd* last_cmd;
namespace prediction {
	void start(player_t* local, c_cmd* cmd) {
		if (last_cmd) {
			if (last_cmd->is_predicted) 
				tick_base = local->tick_base();
			else ++tick_base;
		}
		last_cmd = cmd;
		prev_curtime = csgo::globals->cur_time;
		prev_frametime = csgo::globals->frame_time;

		csgo::globals->cur_time = (tick_base * csgo::globals->interval_per_tick);
		csgo::globals->frame_time = csgo::globals->interval_per_tick;

		csgo::movement->start_track_prediction_errors(local);

		c_move_data data;
		memset(&data, 0, sizeof(c_move_data));

		csgo::movement_helper->set_host(local);
		csgo::prediction->setup_move(local, cmd, csgo::movement_helper, &data);
		csgo::movement->process_movement(local, &data);
		csgo::prediction->finish_move(local, cmd, &data);
	}

	void finish(player_t* local) {
		csgo::movement->finish_track_prediction_errors(local);
		csgo::movement_helper->set_host(nullptr);

		csgo::globals->cur_time = prev_curtime;
		csgo::globals->frame_time = prev_frametime;
	}
}