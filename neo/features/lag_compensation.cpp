#include "lag_compensation.h"
#include "../csgo/interfaces/convar.h"
#include "../csgo/misc/options.h"


	float fov_to_player(vec3_t viewAngle, vec3_t aimAngle) {
		vec3_t delta = aimAngle - viewAngle;
		math::fix_angles(&delta);
		return sqrtf(powf(delta.x, 2.0f) + powf(delta.y, 2.0f));
	}

	bool not_target(player_t* player) {
		if (!player || player == g::local)
			return true;

		if (player->health() <= 0)
			return true;

		int entIndex = player->ent_index();
		return entIndex > csgo::globals->max_clients;
	}

	void bt::on_fsn() {
		player_t* player;
		static con_var* sv_maxunlag = csgo::cvar->find_var(xor("sv_maxunlag"));
		for (int i = 1; i <= csgo::globals->max_clients; ++i) {
			player = player_t::get_player_by_index(i);

			if (not_target(player)) {
				if (data.count(i) > 0)
					data.erase(i); continue;
			}

			if (player->team() == g::local->team()) {
				if (data.count(i) > 0)
					data.erase(i); continue;
			}

			auto& cur_data = data[i];
			if (!cur_data.empty()) {
				auto& front = cur_data.front();

				if (front.sim_time == player->sim_time())
					continue;

				while (!cur_data.empty()) {
					auto& back = cur_data.back();
					float deltaTime = std::clamp(correct_time, 0.f, sv_maxunlag->get_float()) - (csgo::globals->cur_time - back.sim_time);

					if (std::fabsf(deltaTime) <= 0.2f) //will make a slider laiter now im lazy
						break;
					cur_data.pop_back();
				}
			}
			auto model = player->get_model();
			if (!model) continue;
			auto hdr = csgo::model_info->get_studio_model(model);
			if (!hdr) continue;
			auto hitbox_set = hdr->get_hitbox_set(player->hitbox_set());
			auto hitbox_head = hitbox_set->get_hitbox(HITBOX_HEAD);
			auto hitbox_center = (hitbox_head->bbmin + hitbox_head->bbmax) * 0.5f;
			backtrack_data bd;
			bd.hitboxset = hitbox_set;
			bd.sim_time = player->sim_time();
			*(vec3_t*)((uintptr_t)player + 0xA0) = player->vec_origin();
			*(int*)((uintptr_t)player + 0xA68) = 0;
			*(int*)((uintptr_t)player + 0xA30) = 0;
			player->inv_bone_cache();
			player->setup_bones(bd.bone_matrix, 256, 0x7FF00, csgo::globals->cur_time);
			math::vector_transform(hitbox_center, bd.bone_matrix[hitbox_head->bone], bd.hitbox_pos);
			data[i].push_front(bd);
		}
	}

	void bt::on_move(c_cmd* pCmd) {
		if (!csgo::engine->is_ingame() || !g::local || !g::local->is_alive()) {
			data.clear();
			return;
		}
		auto weapon = g::local->active_weapon();
		if (!weapon) {
			data.clear();
			return;
		}
		if (!options::legit::backtrack) {
			data.clear();
			return;
		}
		//cvars
		static con_var* sv_maxunlag = csgo::cvar->find_var(xor ("sv_maxunlag"));
		static con_var* sv_minupdaterate = csgo::cvar->find_var(xor ("sv_minupdaterate"));
		static con_var* sv_maxupdaterate = csgo::cvar->find_var(xor ("sv_maxupdaterate"));
		static con_var* sv_client_min_interp_ratio = csgo::cvar->find_var(xor ("sv_client_min_interp_ratio"));
		static con_var* sv_client_max_interp_ratio = csgo::cvar->find_var(xor ("sv_client_max_interp_ratio"));
		static con_var* cl_interp_ratio = csgo::cvar->find_var(xor ("cl_interp_ratio"));
		static con_var* cl_interp = csgo::cvar->find_var(xor ("cl_interp"));
		static con_var* cl_updaterate = csgo::cvar->find_var(xor ("cl_updaterate"));

		float updaterate = cl_updaterate->get_float();
		float minupdaterate = sv_minupdaterate->get_float();
		float maxupdaterate = sv_maxupdaterate->get_float();
		float min_interp = sv_client_min_interp_ratio->get_float();
		float max_interp = sv_client_max_interp_ratio->get_float();
		float lerp_amount = cl_interp->get_float();
		float lerp_ratio = cl_interp_ratio->get_float();

		lerp_ratio = std::clamp(lerp_ratio, min_interp, max_interp);
		if (lerp_ratio == 0.0f) lerp_ratio = 1.0f;
		float update_rate = std::clamp(updaterate, minupdaterate, maxupdaterate);

		lerp_time = std::fmaxf(lerp_amount, lerp_ratio / update_rate);
		latency = csgo::engine->get_netchan_info()->get_latency(FLOW_INCOMING) + csgo::engine->get_netchan_info()->get_latency(FLOW_OUTGOING);
		correct_time = latency + lerp_time;

		vec3_t local_eye_pos = g::local->eye_pos();
		vec3_t angles;

		int tick_count = -1;
		float best_fov = 255.0f;

		for (auto& node : data) {
			auto& cur_data = node.second;

			if (cur_data.empty())
				continue;

			for (auto& bd : cur_data) {
				float deltaTime = std::clamp(correct_time, 0.f, sv_maxunlag->get_float()) - (csgo::globals->cur_time - bd.sim_time);
				if (std::fabsf(deltaTime) > 0.2f)
					continue;

				math::vector_angles(bd.hitbox_pos - local_eye_pos, angles);
				math::fix_angles(&angles);

				float fov = fov_to_player(pCmd->view_angles, angles);
				if (best_fov > fov) {
					best_fov = fov;
					tick_count = TIME_TO_TICKS(bd.sim_time + lerp_time);
				}
			}
		}
		if (tick_count != -1)
			pCmd->tick_count = tick_count;
	}
	bt g_bt;

void fake_latency::update_sequence() {
	auto net_channel = csgo::client_s->net_channel;
	if (net_channel == nullptr)

	if (m_last_incoming_sequence_number == 0)
		m_last_incoming_sequence_number = net_channel->in_sequence_nr;

	if (net_channel->in_sequence_nr > m_last_incoming_sequence_number) {
		net_channel->in_sequence_nr = net_channel->in_sequence_nr;
		sequences.emplace_front(incoming_sequence_t(net_channel->in_reliable_state, net_channel->out_reliable_state, net_channel->in_sequence_nr, csgo::globals->realtime));
	}

	if (sequences.size() > 2048U)
		sequences.pop_back();
}

void fake_latency::clear_sequence() {
	if (!sequences.empty())
	{
		m_last_incoming_sequence_number = 0;
		sequences.clear();
	}
}

void fake_latency::add_latency(i_net_channel* net_channel) {
	for (auto& seq : sequences) {
		if (csgo::globals->realtime - seq.m_current_time >= (200/*ms*/ / 1000.f)) {
			net_channel->in_reliable_state = seq.m_in_reliable_state;
			net_channel->in_sequence_nr = seq.m_sequence_nr;
			break;
		}
	}
}