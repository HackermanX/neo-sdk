#include "menu.h"
#include "imgui/impl/imgui_impl_dx9.h"
#include "../csgo/sdk.h"
#include "../csgo/misc/input.h"
#include "../csgo/misc/options.h"

namespace menu {
	void init() {
		ImGui::CreateContext();
		ImGui_ImplDX9_Init(input_system::get_main_window(), csgo::d3_device);
		_visible = false;
	}
	void render() {
		//ImGui::GetIO().MouseDrawCursor = _visible; ->disgusting and bugs out
		if (!_visible) return;

		auto flags = ImGuiWindowFlags_NoSavedSettings | NULL | NULL | ImGuiWindowFlags_NoResize | NULL | NULL | NULL | NULL;
		auto flags_alpha = ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_AlphaPreview;
		auto flags_no_alpha = ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip;

		ImGui::SetNextWindowSize({ 400.f, 300.f });

		ImGui::Begin("neo-sdk", nullptr, flags | ImGuiWindowFlags_NoTitleBar);
		{
			ImGui::SetCursorPosX(0.f);
			ImGui::BeginTabBar("for da line", ImGuiTabBarFlags_FittingPolicyScroll | ImGuiTabBarFlags_NoTooltip);
			ImGui::SetCursorPosX(400.f);
			ImGui::EndTabBar();

			ImGui::SetCursorPos({ 115.f, 8.f });
			ImGui::BeginTabBar("features", ImGuiTabBarFlags_FittingPolicyScroll | ImGuiTabBarFlags_NoTooltip);
			if (ImGui::BeginTabItem("legit")) {
				ImGui::SetCursorPosX(5.f);

				ImGui::Checkbox("backtrack", &options::legit::backtrack);

				ImGui::SetCursorPosX(5.f);

				if (options::legit::backtrack)
					ImGui::Checkbox("extended backtrack", &options::legit::fake_latency);
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("esp")) {
				ImGui::SetCursorPosX(5.f);

				ImGui::Checkbox("box esp", &options::esp::box); ImGui::SameLine();
				ImGui::ColorEdit5("##box_color", &options::esp::box_color, flags_alpha);

				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("chams")) {
				ImGui::SetCursorPosX(5.f);

				ImGui::Checkbox("chams", &options::chams::on); ImGui::SameLine();
				ImGui::ColorEdit5("##chams_visible", &options::chams::visible, flags_alpha);

				ImGui::SetCursorPosX(5.f);

				ImGui::Checkbox("chams xqz", &options::chams::xqz); ImGui::SameLine();
				ImGui::ColorEdit5("##chams_invisible", &options::chams::invisible, flags_alpha);
				ImGui::EndTabItem();
			}
			ImGui::SetCursorPosX(250.f);
			if (ImGui::BeginTabItem("misc")) {
				ImGui::SetCursorPosX(5.f);

				ImGui::Checkbox("bhop", &options::move::bhop);

				ImGui::SetCursorPosX(5.f);

				ImGui::Checkbox("watermark", &options::misc::watermark); ImGui::SameLine();
				ImGui::ColorEdit5("##watermark_color", &options::misc::watermark_color, flags_alpha);
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