#include "../hooks.h"
#include "../../features/movement.h"
#include "../../features/prediction.h"
#include "../../features/lag_compensation.h"
#include "../../csgo/misc/options.h"

bool __fastcall hooks::create_move::hook(void* thisptr, int edx, float fl_input_sample_time, c_cmd* cmd) {
	original(thisptr, edx, fl_input_sample_time, cmd);
	g::local = csgo::entity_list->get<player_t>(csgo::engine->get_local_player());
	if (!cmd || !g::local || !cmd->command_number) return original;

	if (options::legit::fake_latency) fake_latency::update_sequence();
	else fake_latency::clear_sequence();

	move::bhop(cmd);

	g_bt.on_move(cmd);

	prediction::start(g::local, cmd);
	prediction::finish(g::local);

	return false;
}