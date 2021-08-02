#include "movement.h"
#include "../csgo/misc/options.h"

namespace move {
	void bhop(c_cmd* cmd) {
		if (!options::bhop) return;
		if (!(g::local->m_flags() & fl_onground))
			cmd->buttons &= ~in_jump;
	}
}