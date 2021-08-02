#pragma once
#include "../csgo/globals.h"

namespace prediction
{
	extern float prev_curtime;
	extern float prev_frametime;

	void start(player_t* local, c_cmd* cmd);
	void finish(player_t* local);
};