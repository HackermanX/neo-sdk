#include "../hooks.h"
#include "../../features/lag_compensation.h"
#include "../../csgo/misc/options.h"

int __fastcall hooks::send_datagram(i_net_channel* thisptr, int edx, bf_write* datagram) {
	static auto o_send_datagram = send_data.get_original<decltype(&send_datagram)>();
	if (!options::legit::fake_latency || !csgo::engine->is_ingame() || !g::local || datagram != nullptr)
		return o_send_datagram(thisptr, edx, datagram);
	int instate = thisptr->in_reliable_state;
	int insequencenr = thisptr->in_sequence_nr;
	fake_latency::add_latency(thisptr);
	const int ret = o_send_datagram(thisptr, edx, datagram);
	thisptr->in_reliable_state = instate;
	thisptr->in_sequence_nr = insequencenr;
	return ret;
}