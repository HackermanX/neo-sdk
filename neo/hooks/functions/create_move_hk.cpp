#include "../hooks.h"
#include "../../features/movement.h"
#include "../../features/prediction.h"
#include "../../features/lag_compensation.h"
#include "../../csgo/misc/options.h"

bool __fastcall hooks::create_move_hk(void* thisptr, int edx, float fl_input_sample_time, c_cmd* cmd) {
	static auto original = create_move.get_original<decltype(&create_move_hk)>();
	original(thisptr, edx, fl_input_sample_time, cmd);
	g::local = csgo::entity_list->get<player_t>(csgo::engine->get_local_player());
	if (!cmd || !g::local || !cmd->command_number) return original;

	auto pre_pred_flags = g::local->m_flags();
	auto netchannel = csgo::client_s->net_channel;

	if (options::fake_latency) fake_latency::update_sequence();
	else fake_latency::clear_sequence();
	if (netchannel != nullptr) {
		if (!send_data.is_hooked())
			send_data.create(get_vfunc(netchannel, 46), &send_datagram);
	} //nasa

	move::bhop(cmd, pre_pred_flags);

	g_bt.on_move(cmd);

	prediction::start(g::local, cmd);
	prediction::finish(g::local);

	return false;
}