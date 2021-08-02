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
		auto flags_alpha = ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_AlphaPreview;
		auto flags_no_alpha = ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip;

		ImGui::SetNextWindowSize({ 185.f, 150.f });

		ImGui::Begin("neo-sdk", nullptr, flags);
		{
			ImGui::BeginTabBar("stuff", ImGuiTabBarFlags_Reorderable | ImGuiTabBarFlags_FittingPolicyScroll | ImGuiTabBarFlags_NoTooltip);
			if (ImGui::BeginTabItem("legit")) {
				ImGui::Checkbox("backtrack", &options::legit::backtrack);
				ImGui::Checkbox("extendo", &options::legit::fake_latency);
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("esp")) {
				ImGui::Checkbox("box esp", &options::esp::box); ImGui::SameLine();
				ImGui::ColorEdit5("##box color", &options::esp::box_color, flags_alpha);
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("chams")) {
				ImGui::Checkbox("chams", &options::chams::on); ImGui::SameLine();
				ImGui::ColorEdit5("##chams visible", &options::chams::visible, flags_alpha);
				ImGui::Checkbox("chams xqz", &options::chams::xqz); ImGui::SameLine();
				ImGui::ColorEdit5("##chams invisible", &options::chams::invisible, flags_alpha);
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("misc")) {
				ImGui::Checkbox("bhop", &options::move::bhop);
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
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