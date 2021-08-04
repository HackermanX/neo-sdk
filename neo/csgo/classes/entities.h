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

enum itemdefinition_index
{
	WEAPON_NONE,
	WEAPON_DEAGLE,
	WEAPON_ELITE,
	WEAPON_FIVESEVEN,
	WEAPON_GLOCK,
	WEAPON_AK47 = 7,
	WEAPON_AUG,
	WEAPON_AWP,
	WEAPON_FAMAS,
	WEAPON_G3SG1,
	WEAPON_GALILAR = 13,
	WEAPON_M249,
	WEAPON_M4A1 = 16,
	WEAPON_MAC10,
	WEAPON_P90 = 19,
	WEAPON_ZONE_REPULSOR,
	WEAPON_MP5SD = 23,
	WEAPON_UMP45,
	WEAPON_XM1014,
	WEAPON_BIZON,
	WEAPON_MAG7,
	WEAPON_NEGEV,
	WEAPON_SAWEDOFF,
	WEAPON_TEC9,
	WEAPON_TASER,
	WEAPON_HKP2000,
	WEAPON_MP7,
	WEAPON_MP9,
	WEAPON_NOVA,
	WEAPON_P250,
	WEAPON_SHIELD,
	WEAPON_SCAR20,
	WEAPON_SG553,
	WEAPON_SSG08,
	WEAPON_KNIFEGG,
	WEAPON_KNIFE,
	WEAPON_FLASHBANG,
	WEAPON_HEGRENADE,
	WEAPON_SMOKEGRENADE,
	WEAPON_MOLOTOV,
	WEAPON_DECOY,
	WEAPON_INCGRENADE,
	WEAPON_C4,
	WEAPON_HEALTHSHOT = 57,
	WEAPON_KNIFE_T = 59,
	WEAPON_M4A1_SILENCER,
	WEAPON_USP_SILENCER,
	WEAPON_CZ75A = 63,
	WEAPON_REVOLVER,
	WEAPON_TAGRENADE = 68,
	WEAPON_FISTS,
	WEAPON_BREACHCHARGE,
	WEAPON_TABLET = 72,
	WEAPON_MELEE = 74,
	WEAPON_AXE,
	WEAPON_HAMMER,
	WEAPON_SPANNER = 78,
	WEAPON_KNIFE_GHOST = 80,
	WEAPON_FIREBOMB,
	WEAPON_DIVERSION,
	WEAPON_FRAG_GRENADE,
	WEAPON_SNOWBALL,
	WEAPON_BUMPMINE,
	WEAPON_KNIFE_BAYONET = 500,
	WEAPON_KNIFE_CSS = 503,
	WEAPON_KNIFE_FLIP = 505,
	WEAPON_KNIFE_GUT,
	WEAPON_KNIFE_KARAMBIT,
	WEAPON_KNIFE_M9_BAYONET,
	WEAPON_KNIFE_TACTICAL,
	WEAPON_KNIFE_FALCHION = 512,
	WEAPON_KNIFE_SURVIVAL_BOWIE = 514,
	WEAPON_KNIFE_BUTTERFLY,
	WEAPON_KNIFE_PUSH,
	WEAPON_KNIFE_CORD,
	WEAPON_KNIFE_CANIS,
	WEAPON_KNIFE_URSUS,
	WEAPON_KNIFE_GYPSY_JACKKNIFE,
	WEAPON_KNIFE_OUTDOOR,
	WEAPON_KNIFE_STILETTO,
	WEAPON_KNIFE_WIDOWMAKER,
	WEAPON_KNIFE_SKELETON = 525,
	GLOVE_STUDDED_BLOODHOUND = 5027,
	GLOVE_T_SIDE = 5028,
	GLOVE_CT_SIDE = 5029,
	GLOVE_SPORTY = 5030,
	GLOVE_SLICK = 5031,
	GLOVE_LEATHER_WRAP = 5032,
	GLOVE_MOTORCYCLE = 5033,
	GLOVE_SPECIALIST = 5034,
	GLOVE_HYDRA = 5035
};

enum weapon_type
{
	WEAPONTYPE_KNIFE = 0,
	WEAPONTYPE_PISTOL,
	WEAPONTYPE_SUBMACHINEGUN,
	WEAPONTYPE_RIFLE,
	WEAPONTYPE_SHOTGUN,
	WEAPONTYPE_SNIPER_RIFLE,
	WEAPONTYPE_MACHINEGUN,
	WEAPONTYPE_C4,
	WEAPONTYPE_PLACEHOLDER,
	WEAPONTYPE_GRENADE,
	WEAPONTYPE_UNKNOWN
};

class entity_t;
class base_weapon {
public:
	netvar(int, weapon, xor ("DT_BaseViewModel"), xor ("m_hWeapon"));
	netvar(short, item_definition_index, xor ("DT_BaseCombatWeapon"), xor ("m_iItemDefinitionIndex"));
	netvar(int, clip, xor ("DT_BaseCombatWeapon"), xor ("m_iClip1"));
	netvar(int, zoom_level, xor ("DT_WeaponCSBaseGun"), xor ("m_zoomLevel"));

	int weapon_index = item_definition_index();

	bool sniper() {
		if (!this)
			return false;

		return weapon_index == WEAPON_AWP || weapon_index == WEAPON_SCAR20 || weapon_index == WEAPON_G3SG1 || weapon_index == WEAPON_SSG08;
	}

	bool rifle() {
		if (!this)
			return false;

		return weapon_index == WEAPON_AK47 || weapon_index == WEAPON_M4A1 || weapon_index == WEAPON_M4A1_SILENCER || weapon_index == WEAPON_GALILAR || weapon_index == WEAPON_FAMAS || weapon_index == WEAPON_AUG || weapon_index == WEAPON_SG553;
	}

	bool smg() {
		if (!this)
			return false;

		return weapon_index == WEAPON_MAC10 || weapon_index == WEAPON_MP7 || weapon_index == WEAPON_MP9 || weapon_index == WEAPON_P90 || weapon_index == WEAPON_BIZON || weapon_index == WEAPON_UMP45 || weapon_index == WEAPON_MP5SD;
	}

	bool shotgun() {
		if (!this)
			return false;

		return weapon_index == WEAPON_XM1014 || weapon_index == WEAPON_NOVA || weapon_index == WEAPON_SAWEDOFF || weapon_index == WEAPON_MAG7 || weapon_index == WEAPON_M249 || weapon_index == WEAPON_NEGEV;
	}

	bool pistol() {
		if (!this)
			return false;

		return  weapon_index == WEAPON_ELITE || weapon_index == WEAPON_FIVESEVEN || weapon_index == WEAPON_P250 || weapon_index == WEAPON_GLOCK || weapon_index == WEAPON_HKP2000 || weapon_index == WEAPON_CZ75A || weapon_index == WEAPON_USP_SILENCER || weapon_index == WEAPON_TEC9;
	}

	bool heavy_pistol() {
		if (!this)
			return false;

		return weapon_index == WEAPON_DEAGLE || weapon_index == WEAPON_REVOLVER;
	}

	bool knife() {
		if (!this)
			return false;

		return weapon_index == WEAPON_KNIFE || weapon_index == WEAPON_KNIFE_BAYONET || weapon_index == WEAPON_KNIFE_BUTTERFLY || weapon_index == WEAPON_KNIFE_FALCHION || weapon_index == WEAPON_KNIFE_FLIP || weapon_index == WEAPON_KNIFE_GUT || weapon_index == WEAPON_KNIFE_KARAMBIT || weapon_index == WEAPON_KNIFE_M9_BAYONET || weapon_index == WEAPON_KNIFE_PUSH || weapon_index == WEAPON_KNIFE_SURVIVAL_BOWIE || weapon_index == WEAPON_KNIFE_T || weapon_index == WEAPON_KNIFE_TACTICAL || weapon_index == WEAPON_KNIFEGG || weapon_index == WEAPON_KNIFE_GHOST || weapon_index == WEAPON_KNIFE_GYPSY_JACKKNIFE || weapon_index == WEAPON_KNIFE_STILETTO || weapon_index == WEAPON_KNIFE_URSUS || weapon_index == WEAPON_KNIFE_WIDOWMAKER || weapon_index == WEAPON_KNIFE_CSS || weapon_index == WEAPON_KNIFE_CANIS || weapon_index == WEAPON_KNIFE_CORD || weapon_index == WEAPON_KNIFE_OUTDOOR || weapon_index == WEAPON_KNIFE_SKELETON;
	}

	bool zeus() {
		if (!this)
			return false;

		return weapon_index == WEAPON_TASER;
	}

	bool c4() {
		if (!this)
			return false;

		return weapon_index == WEAPONTYPE_C4;
	}

	int weapon_group()
	{
		if (!this)
			return -1;

		if (sniper())
			return 0;
		else if (heavy_pistol())
			return 1;
		else if (pistol())
			return 2;
		else if (rifle())
			return 3;
		else if (smg())
			return 4;
		else if (shotgun())
			return 5;
		else if (knife())
			return 6;
		else if (zeus())
			return 7;
		else if (c4())
			return 8;

		return -1;
	}

	bool can_shoot() {
		if (!this)
			return false;

		return sniper() || heavy_pistol() || pistol() || rifle() || smg() || shotgun() || zeus();
	}

	std::string name()
	{
		if (!this)
			return " ";

		switch (item_definition_index())
		{
		case WEAPON_KNIFE:
		case WEAPON_KNIFE_T:
		case WEAPON_KNIFE_KARAMBIT:
		case WEAPON_KNIFE_M9_BAYONET:
		case WEAPON_KNIFE_BAYONET:
		case WEAPON_KNIFE_BUTTERFLY:
		case WEAPON_KNIFE_PUSH:
		case WEAPON_KNIFE_GUT:
		case WEAPON_KNIFE_SURVIVAL_BOWIE:
		case WEAPON_KNIFE_FLIP:
		case WEAPON_KNIFE_FALCHION:
		case WEAPON_KNIFE_TACTICAL:
			return "knife";
		case WEAPON_GLOCK:
			return "glock18";
		case WEAPON_USP_SILENCER:
			return "usp-s";
		case WEAPON_HKP2000:
			return "p2000";
		case WEAPON_ELITE:
			return "dual barettas";
		case WEAPON_P250:
			return "p250";
		case WEAPON_FIVESEVEN:
			return "five-seven";
		case WEAPON_TEC9:
			return "tec9";
		case WEAPON_CZ75A:
			return "c75-a";
		case WEAPON_DEAGLE:
			return "deagle";
		case WEAPON_REVOLVER:
			return "r8";
		case WEAPON_XM1014:
			return "xm1014";
		case WEAPON_SAWEDOFF:
			return "sawed-off";
		case WEAPON_MAG7:
			return "mag-7";
		case WEAPON_NOVA:
			return "nova";
		case WEAPON_NEGEV:
			return "negev";
		case WEAPON_M249:
			return "m249";
		case WEAPON_MAC10:
			return "mac10";
		case WEAPON_UMP45:
			return "ump45";
		case WEAPON_BIZON:
			return "pp-bizon";
		case WEAPON_MP7:
			return "mp7";
		case WEAPON_MP9:
			return "mp9";
		case WEAPON_P90:
			return "p90";
		case WEAPON_GALILAR:
			return "galil ar";
		case WEAPON_FAMAS:
			return "famas";
		case WEAPON_M4A1_SILENCER:
			return "m4a1-s";
		case WEAPON_M4A1:
			return "m4a4";
		case WEAPON_AK47:
			return "ak47";
		case WEAPON_AUG:
			return "aug";
		case WEAPON_SG553:
			return "sg553";
		case WEAPON_G3SG1:
			return "g3sg1";
		case WEAPON_SCAR20:
			return "scar20";
		case WEAPON_SSG08:
			return "ssg08";
		case WEAPON_AWP:
			return "awp";
		case WEAPON_TASER:
			return "zeus x27";
		case WEAPON_FLASHBANG:
			return "flashbang";
		case WEAPON_HEGRENADE:
			return "he grenade";
		case WEAPON_SMOKEGRENADE:
			return "smoke grenade";
		case WEAPON_MOLOTOV:
			return "molotov";
		case WEAPON_DECOY:
			return "decoy";
		case WEAPON_INCGRENADE:
			return "incendiary";
		case WEAPON_C4:
			return "c4";
		}
	}
};

class entity_t : public i_client_entity {
public:
	static __forceinline entity_t* get_entity_by_index(int index) {
		return static_cast<entity_t*>(csgo::entity_list->get_client_entity(index));
	}
	const matrix3x4_t& coordinate_frame()
	{
		static auto _coordinate_frame = netvars.get_offset(xor ("DT_BaseEntity"), "m_CollisionGroup") - 0x30;
		return *(matrix3x4_t*)((uintptr_t)this + _coordinate_frame);
	}
	netvar(int32_t, team, xor ("DT_BaseEntity"), xor ("m_iTeamNum"));
	netvar(bool, spotted, xor ("DT_BaseEntity"), xor ("m_bSpotted"));
	netvar(int, health, xor ("DT_BasePlayer"), xor ("m_iHealth"));
	netvar(c_handle <base_weapon>, active_weapon, xor ("DT_BaseCombatCharacter"), xor ("m_hActiveWeapon"));
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
	netvar(int, health, xor ("DT_BasePlayer"), xor ("m_iHealth"));
	netvar(int, life_state, xor ("DT_BasePlayer"), xor ("m_lifeState"));
	netvar(bool, is_scoped, xor ("DT_BasePlayer"), xor ("m_bIsScoped"));
	netvar(bool, tick_base, xor ("DT_BasePlayer"), xor ("m_nTickBase"));
	netvar(int32_t, m_flags, ("DT_BasePlayer"), ("m_fFlags"));
	netvar(vec3_t, vec_origin, xor ("DT_BaseEntity"), xor ("m_vecOrigin"));
	netvar(float, sim_time, xor ("DT_BaseEntity"), xor ("m_flSimulationTime"));
	netvar(int32_t, hitbox_set, xor ("DT_BaseAnimating"), xor ("m_nHitboxSet"));
	netvar(c_handle<base_weapon>, active_weapon, xor ("DT_BaseCombatCharacter"), xor ("m_hActiveWeapon"));
	netvar(vec3_t, view_offset, xor ("DT_BasePlayer"), xor ("m_vecViewOffset[0]"));
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
		static DWORD addr = (DWORD)utils::pattern_scan(xor ("client.dll"), xor ("80 3D ? ? ? ? ? 74 16 A1 ? ? ? ? 48 C7 81"));

		*(int*)((uintptr_t)this + 0xA30) = csgo::globals->frame_count; //we'll skip occlusion checks now
		*(int*)((uintptr_t)this + 0xA28) = 0;//clear occlusion flags

		unsigned long model_bone_counter = **(unsigned long**)(addr + 10);
		*(unsigned int*)((DWORD)this + 0x2924) = 0xFF7FFFFF; // m_flLastBoneSetupTime = -FLT_MAX;
		*(unsigned int*)((DWORD)this + 0x2690) = (model_bone_counter - 1); // m_iMostRecentModelBoneCounter = g_iModelBoneCounter - 1;
	}
};