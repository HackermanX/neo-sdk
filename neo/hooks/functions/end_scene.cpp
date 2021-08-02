#include "../hooks.h"
#include "../../rendering/imgui/imgui.h"
#include "../../rendering/menu.h"
#include "../../features/esp.h"

long __stdcall hooks::end_scene_hk(IDirect3DDevice9* device) {
	static auto original = end_scene.get_original<decltype(&end_scene_hk)>();
	IDirect3DStateBlock9* pixel_state = NULL;
	IDirect3DVertexDeclaration9* vertDec;
	IDirect3DVertexShader9* vertShader;

	device->CreateStateBlock(D3DSBT_PIXELSTATE, &pixel_state);
	device->GetVertexDeclaration(&vertDec);
	device->GetVertexShader(&vertShader);

	device->SetRenderState(D3DRS_COLORWRITEENABLE, 0xffffffff);

	ImGui_ImplDX9_NewFrame();

	g::draw_list = ImGui::GetOverlayDrawList();

	menu::render();
	ImGui::GetStyle().AntiAliasedLines = true; //seems to look slightly better (maybe just my eyes fooling me)
	esp::draw_list();
	ImGui::Render();

	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	pixel_state->Apply();
	pixel_state->Release();
	device->SetVertexDeclaration(vertDec);
	device->SetVertexShader(vertShader);
	return original(device);
}