#include "movement.h"
#include "../csgo/misc/options.h"

namespace move {
	void bhop(c_cmd* cmd, int pre_flags) {
		if (!options::bhop) return;
		const int move_type = g::local->move_type();
		if (!(g::local->m_flags() & fl_onground))
			cmd->buttons &= ~in_jump;
	}
}