#pragma once
#include <Windows.h>
#include <string>
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#include "imgui/imgui.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui/imgui_internal.h"
#define IM_USE using namespace ImGui;

namespace menu {
	static bool _visible;
	static ImGuiStyle        style;
	void init();
	void render();
	void toggle();
	bool is_visible();
}