#pragma once
#include "../math/vector_3d.h"

#define in_attack (1 << 0)
#define in_jump (1 << 1)
#define in_duck (1 << 2)
#define in_forward (1 << 3)
#define in_back  (1 << 4)
#define in_use  (1 << 5)
#define in_cancel  (1 << 6)
#define in_left  (1 << 7)
#define in_right  (1 << 8)
#define in_moveleft  (1 << 9)
#define in_moveright  (1 << 10)
#define in_attack2  (1 << 11)
#define in_run  (1 << 12)
#define in_reload  (1 << 13)
#define in_alt1  (1 << 14)
#define in_alt2  (1 << 15)
#define in_score  (1 << 16)
#define in_speed  (1 << 17)
#define in_walk  (1 << 18)
#define in_zoom  (1 << 19)
#define in_weapon1  (1 << 20)
#define in_weapon2  (1 << 21)
#define in_bullrush  (1 << 22)
#define in_grenade1  (1 << 23)
#define in_grenade2  (1 << 24)
#define in_attack3  (1 << 25

class c_cmd
{
public:
	c_cmd() {};
	virtual ~c_cmd() {};
	int command_number;
	int tick_count;
	vec3_t view_angles;
	vec3_t aim_direction;
	float forward_move;
	float side_move;
	float up_move;
	int buttons;
	unsigned char impulse;
	int weapon_select;
	int weapon_subtype;
	int random_seed;
	short mouse_dx;
	short mouse_dy;
	bool is_predicted;
	char pad_0x4c[0x18];
};