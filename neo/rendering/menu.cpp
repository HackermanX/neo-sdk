#include "menu.h"
#include "imgui/impl/imgui_impl_dx9.h"
#include "../csgo/sdk.h"
#include "../csgo/misc/input.h"
#include "../csgo/misc/options.h"

namespace menu {
	void init() {
		ImGui::CreateContext();
		ImGui_ImplDX9_Init(input_system::get_main_window(), csgo::d3_device);
		_visible = true;
	}
	void render() {
		ImGui::GetIO().MouseDrawCursor = _visible;
		if (!_visible) return;
		auto flags = ImGuiWindowFlags_NoSavedSettings | NULL | NULL | ImGuiWindowFlags_NoResize | NULL | NULL | NULL | NULL;

		ImGui::SetNextWindowSize({ 150.f, 150.f });

		ImGui::Begin("neo-sdk", nullptr, flags);
		{
			ImGui::Checkbox("bhop", &options::bhop);
			ImGui::Checkbox("box esp", &options::box);
			ImGui::Checkbox("backtrack", &options::backtrack);
			ImGui::Checkbox("extendo", &options::fake_latency);
		}
		ImGui::End();
	}
	void toggle()
	{
		_visible = !_visible;
	}
	bool is_visible()
	{
		return _visible;
	}
}