#pragma once
#define NOMINMAX
#include <Windows.h>
#include "classes/user_cmd.h"
#include "interfaces/base_client_dll.h"
#include "interfaces/global_vars.h"
#include "utilities/utils.h"
#include "interfaces/entity_list.h"
#include "interfaces/engine.h"
#include "utilities/xor.h"
#include "netvars/netvars.h"
#include "classes/pred.h"
#include "interfaces/i_client_entity.h"
#include "interfaces/iv_model_info_client.h"
#include "interfaces/client_mode.h"
#include "interfaces/i_cvar.h"
#include "interfaces/client_state.h"
#include "interfaces/i_surface.h"
#include "interfaces/input_system.h"
#include "interfaces/iv_model_render.h"
#include "interfaces/i_material_system.h"

struct IDirect3DDevice9;

namespace csgo {
	inline i_base_client_dll* client;
	inline c_global_vars_base* globals;
	inline i_client_entity_list* entity_list;
	inline iv_engine_client* engine;
	inline c_game_movement* movement;
	inline c_move_helper* movement_helper;
	inline c_prediction* prediction;
	inline IDirect3DDevice9* d3_device;
	inline iv_model_info_client* model_info;
	inline i_client_mode* client_mode;
	inline i_cvar* cvar;
	inline client_state* client_s;
	inline i_surface* surface;
	inline i_input_sys* input;
	inline iv_model_render* model_render;
	inline i_material_system* material_system;

	__forceinline void init() {
		client = utils::create_interface<i_base_client_dll>(xor("client.dll"), xor("VClient018"));
		entity_list = utils::create_interface<i_client_entity_list>(xor("client.dll"), xor("VClientEntityList003"));
		engine = utils::create_interface<iv_engine_client>(xor("engine.dll"), xor("VEngineClient014"));
		movement = utils::create_interface<c_game_movement>(xor("client.dll"), xor("GameMovement001"));
		prediction = utils::create_interface<c_prediction>(xor("client.dll"), xor("VClientPrediction001"));
		model_info = utils::create_interface<iv_model_info_client>(xor("engine.dll"), xor("VModelInfoClient004"));
		cvar = utils::create_interface<i_cvar>(xor("vstdlib.dll"), xor("VEngineCvar007"));
		surface = utils::create_interface<i_surface>(xor("vguimatsurface.dll"), xor("VGUI_Surface031"));
		input = utils::create_interface<i_input_sys>(xor("inputsystem.dll"), xor("InputSystemVersion001"));
		model_render = utils::create_interface<iv_model_render>(xor("engine.dll"), xor("VEngineModel016"));
		material_system = utils::create_interface<i_material_system>(xor("materialsystem.dll"), xor("VMaterialSystem080"));

		client_mode = **reinterpret_cast<i_client_mode***>((*reinterpret_cast<uintptr_t**>(client))[10] + 5);
		globals = **reinterpret_cast<c_global_vars_base***>((utils::pattern_scan(xor("client.dll"), xor("A1 ? ? ? ? 5E 8B 40 10")) + 1));
		movement_helper = **reinterpret_cast<c_move_helper***>((utils::pattern_scan(xor ("client.dll"), xor ("8B 0D ? ? ? ? 8B 45 ? 51 8B D4 89 02 8B 01")) + 2));
		d3_device = **reinterpret_cast<IDirect3DDevice9***>((utils::pattern_scan(xor ("shaderapidx9.dll"), xor ("A1 ? ? ? ? 50 8B 08 FF 51 0C")) + 1));
		client_s = **reinterpret_cast<client_state***>((utils::pattern_scan(xor ("engine.dll"), xor ("A1 ? ? ? ? 8B 80 ? ? ? ? C3")) + 1));
	}

	__forceinline void dump() {
        #define stringify_impl(s) #s
        #define stringify(s) stringify_impl(s)
        #define print_interface(name) utils::console_print(xor("%-20s: %p\n"), stringify(name), name)
        print_interface(client);
		print_interface(client_mode);
        print_interface(globals);
		print_interface(entity_list);
		print_interface(engine);
		print_interface(movement);
		print_interface(prediction);
		print_interface(movement_helper);
		print_interface(d3_device);
		print_interface(model_info);
		print_interface(cvar);
		print_interface(client_s);
		print_interface(surface);
		print_interface(input);
		print_interface(model_render);
		print_interface(material_system);
    }
}