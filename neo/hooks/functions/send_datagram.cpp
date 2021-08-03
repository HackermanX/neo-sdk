#include "../hooks.h"
#include "../../features/lag_compensation.h"
#include "../../csgo/misc/options.h"

int __fastcall hooks::send_datagram::hook(i_net_channel* thisptr, int edx, bf_write* datagram) {
	if (!options::legit::fake_latency || !csgo::engine->is_ingame() || !g::local || datagram != nullptr)
		return original(thisptr, edx, datagram);
	int instate = thisptr->in_reliable_state;
	int insequencenr = thisptr->in_sequence_nr;
	fake_latency::add_latency(thisptr);
	const int ret = original(thisptr, edx, datagram);
	thisptr->in_reliable_state = instate;
	thisptr->in_sequence_nr = insequencenr;
	return ret;
}