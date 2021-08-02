#pragma once
#include <windows.h>
#include <cstdint>
#include <algorithm>
#include <sstream>
#include <vector>
#include "../../rendering/imgui/imgui.h"
#include "../misc/color.h"

namespace utils {
	uint8_t* pattern_scan(const char* module_name, const std::string_view signature);
	void attach_console();
	void detach_console();
	bool console_print(const char* fmt, ...);
	void* create_interface(const char* module_name, const char* iface_name);
	ImU32 to_im32(const color& color, const float& alpha);
	template<typename t>
	t* create_interface(const char* module_name, const char* iface_name) {
		return reinterpret_cast<t*>(create_interface(module_name, iface_name));
	}

}