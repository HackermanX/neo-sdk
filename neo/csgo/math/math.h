#pragma once
#include "vector_3d.h"
#include "v_matrix.h"
#include "../sdk.h"

#define TICK_INTERVAL (csgo::globals->interval_per_tick)
#define TICKS_TO_TIME(t) (csgo::globals->interval_per_tick * (t))
#define TIME_TO_TICKS(dt)((int)( 0.5f + (float)(dt) / TICK_INTERVAL))

namespace math {
    void vector_transform(const vec3_t& in1, const matrix3x4_t& in2, vec3_t& out);
    static bool screen_transform(const vec3_t& in, vec3_t& out);
    bool w2s(const vec3_t& in, vec3_t& out);
    void vector_angles(const vec3_t& forward, vec3_t& angles);
	void fix_angles(vec3_t* angles);
}