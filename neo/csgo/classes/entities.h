#pragma once
#include "../netvars/netvars.h"
#include "../utilities/xor.h"
#include "../sdk.h"
#include "../math/math.h"
#include "../misc/e_handle.h"

#define netvar(type, name, table, netvar)                           \
    type& name##() const {                                          \
        static int _##name = netvars.get_offset(table, netvar);     \
        return *(type*)((uintptr_t)this + _##name);                 \
    }

enum entity_flags
{
	fl_onground = (1 << 0),
	fl_ducking = (1 << 1),
	fl_waterjump = (1 << 2),
	fl_ontrain = (1 << 3),
	fl_inrain = (1 << 4),
	fl_frozen = (1 << 5),
	fl_atcontrols = (1 << 6),
	fl_client = (1 << 7),
	fl_fakeclient = (1 << 8),
	fl_inwater = (1 << 9),
	fl_fly = (1 << 10),
	fl_swim = (1 << 11),
	fl_conveyor = (1 << 12),
	fl_npc = (1 << 13),
	fl_godmode = (1 << 14),
	fl_notarget = (1 << 15),
	fl_aimtarget = (1 << 16),
	fl_partialground = (1 << 17),
	fl_staticprop = (1 << 18),
	fl_graphed = (1 << 19),
	fl_grenade = (1 << 20),
	fl_stepmovement = (1 << 21),
	fl_donttouch = (1 << 22),
	fl_basevelocity = (1 << 23),
	fl_worldbrush = (1 << 24),
	fl_object = (1 << 25),
	fl_killme = (1 << 26),
	fl_onfire = (1 << 27),
	fl_dissolving = (1 << 28),
	fl_transragdoll = (1 << 29),
	fl_unblockable_by_player = (1 << 30)
};

enum move_type
{
	movetype_none = 0,
	movetype_isometric,
	movetype_walk,
	movetype_step,
	movetype_fly,
	movetype_flygravity,
	movetype_vphycics,
	movetype_push,
	movetype_noclip,
	movetype_ladder,
	movetype_observer,
	movetype_custom,
	movetype_last = movetype_custom,
	movetype_max_bits = 4,
	max_movetype
};

class entity_t;
class base_weapon;

class entity_t : public i_client_entity {
public:
	static __forceinline entity_t* get_entity_by_index(int index) {
		return static_cast<entity_t*>(csgo::entity_list->get_client_entity(index));
	}
	const matrix3x4_t& coordinate_frame()
	{
		static auto _coordinate_frame = netvars.get_offset(xor("DT_BaseEntity"), "m_CollisionGroup") - 0x30;
		return *(matrix3x4_t*)((uintptr_t)this + _coordinate_frame);
	}
	netvar(int32_t, team, xor("DT_BaseEntity"), xor("m_iTeamNum"));
	netvar(bool, spotted, xor("DT_BaseEntity"), xor("m_bSpotted"));
	netvar(int, health, xor ("DT_BasePlayer"), xor ("m_iHealth"));
	bool is_alive()
	{
		return health() > 0;
	}
};

class player_t : public entity_t {
public:
	static __forceinline player_t* get_player_by_index(int index) {
		return static_cast<player_t*>(get_entity_by_index(index));
	}
	netvar(int, health, xor("DT_BasePlayer"), xor("m_iHealth"));
	netvar(int, life_state, xor("DT_BasePlayer"), xor("m_lifeState"));
	netvar(bool, is_scoped, xor("DT_BasePlayer"), xor("m_bIsScoped"));
	netvar(bool, tick_base, xor ("DT_BasePlayer"), xor ("m_nTickBase"));
	netvar(int32_t, m_flags, ("DT_BasePlayer"), ("m_fFlags"));
	netvar(vec3_t, vec_origin, xor("DT_BaseEntity"), xor("m_vecOrigin"));
	netvar(float, sim_time, xor("DT_BaseEntity"), xor("m_flSimulationTime"));
	netvar(int32_t, hitbox_set, xor("DT_BaseAnimating"), xor("m_nHitboxSet"));
	netvar(c_handle<base_weapon>, active_weapon, xor("DT_BaseCombatCharacter"), xor("m_hActiveWeapon"));
	netvar(vec3_t, view_offset, xor("DT_BasePlayer"), xor("m_vecViewOffset[0]"));
	bool is_alive()
	{
		return health() > 0;
	}
	int move_type()
	{
		return *(int*)(uintptr_t(this) + 0x25C);
	}
	vec3_t eye_pos()
	{
		return vec_origin() + view_offset();
	}
	vec3_t get_hitbox_pos(int hitbox_id) {
		matrix3x4_t bone_matrix[MAXSTUDIOBONES];
		if (setup_bones(bone_matrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, 0.0f)) {
			auto studio_model = csgo::model_info->get_studio_model(get_model());
			if (studio_model) {
				auto hitbox = studio_model->get_hitbox_set(0)->get_hitbox(hitbox_id);
				if (hitbox) {
					auto min = vec3_t{}, max = vec3_t{};

					math::vector_transform(hitbox->bbmin, bone_matrix[hitbox->bone], min);
					math::vector_transform(hitbox->bbmax, bone_matrix[hitbox->bone], max);

					return (min + max) / 2.0f;
				}
			}
		}
		return vec3_t{};
	}
	void inv_bone_cache()
	{
		static DWORD addr = (DWORD)utils::pattern_scan(xor("client.dll"), xor("80 3D ? ? ? ? ? 74 16 A1 ? ? ? ? 48 C7 81"));

		*(int*)((uintptr_t)this + 0xA30) = csgo::globals->frame_count; //we'll skip occlusion checks now
		*(int*)((uintptr_t)this + 0xA28) = 0;//clear occlusion flags

		unsigned long model_bone_counter = **(unsigned long**)(addr + 10);
		*(unsigned int*)((DWORD)this + 0x2924) = 0xFF7FFFFF; // m_flLastBoneSetupTime = -FLT_MAX;
		*(unsigned int*)((DWORD)this + 0x2690) = (model_bone_counter - 1); // m_iMostRecentModelBoneCounter = g_iModelBoneCounter - 1;
	}
};