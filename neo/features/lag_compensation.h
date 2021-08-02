#pragma once
#include <deque>
#include <map>
#include "../csgo/globals.h"

struct backtrack_data {
	player_t*           player;
	float               sim_time;
	mstudiohitboxset_t* hitboxset;
	vec3_t              hitbox_pos;
	matrix3x4_t         bone_matrix[256];//maybe
};

class bt {
public:
	void on_fsn();
	void on_move(c_cmd* pCmd);
	float correct_time = 0.0f;
	float latency = 0.0f;
	float lerp_time = 0.0f;
	std::map<int, std::deque<backtrack_data>> data;
};
extern bt g_bt;

namespace fake_latency {
	struct incoming_sequence_t {
		incoming_sequence_t::incoming_sequence_t(int instate, int outstate, int seqnr, float time) {
			m_in_reliable_state = instate;
			m_out_reliable_state = outstate;
			m_sequence_nr = seqnr;
			m_current_time = time;
		}
		int m_in_reliable_state;
		int m_out_reliable_state;
		int m_sequence_nr;
		float m_current_time;
	};
	static std::deque< incoming_sequence_t > sequences;
	static int m_last_incoming_sequence_number;
	static bool flipped_state = false;
	void update_sequence();
	void clear_sequence();
	void add_latency(i_net_channel* net_channel);
}