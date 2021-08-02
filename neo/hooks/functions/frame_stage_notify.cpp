#include "../hooks.h"
#include "../../csgo/misc/options.h"
#include "../../features/lag_compensation.h"

void __stdcall hooks::fsn_hk(frame_stage stage) {
	using fn = void(__thiscall*)(i_base_client_dll*, frame_stage);
	static auto original = fsn.get_original<fn>();
	if (!csgo::engine->is_ingame() || !g::local) {
		fake_latency::clear_sequence();
		return original(csgo::client, stage);
	}
	static auto set_interpolation_flags = [](player_t* e, int flag) {
		const auto var_map = (uintptr_t)e + 36;
		const auto sz_var_map = *(int*)(var_map + 20);
		for (auto index = 0; index < sz_var_map; index++)
			*(uintptr_t*)((*(uintptr_t*)var_map) + index * 12) = flag;
	};

	switch (stage) {
	case frame_stage::NET_UPDATE_POSTDATAUPDATE_START:
		break;
	case frame_stage::NET_UPDATE_POSTDATAUPDATE_END:
		break;
	case frame_stage::NET_UPDATE_END:
		if (options::backtrack && g::local && g::local->is_alive()) {
			for (uint32_t i = 1; i <= csgo::globals->max_clients; i++) {
				player_t* player = reinterpret_cast<player_t*>(csgo::entity_list->get_client_entity(i));
				if (!player || player->team() == g::local->team()
					|| player == g::local || player->is_dormant())
					continue;
				set_interpolation_flags(player, 0); // disable interpolation
			}
		}
		break;
	case frame_stage::RENDER_START:
		g_bt.on_fsn();
		break;
	} 
	return original(csgo::client, stage);
}