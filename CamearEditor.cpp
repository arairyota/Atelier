#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "camera.h"
#include "CamearEditor.h"

#include "scene.h"

void CamearEditor::Init()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(GetWindow());
	ImGui_ImplDX11_Init(CRenderer::GetDevice(), CRenderer::GetDeviceContext());

	// ウインドウの表示(初期化処理の後に行う)
	ShowWindow(GetWindow(), SW_SHOWDEFAULT);
	UpdateWindow(GetWindow());
}

void CamearEditor::Uninit()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void CamearEditor::Update()
{
	
}

void CamearEditor::Draw()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (_show_demo_window) {
		ImGui::ShowDemoWindow(&_show_demo_window);
	}

	{
		ImGui::SetNextWindowSize(ImVec2(320, 100), 0);
		ImGui::Begin("hoge", &_show_another_window);
		ImGui::Text("fugafuga");
		ImGui::End();
	}

	// Renderin
	ImGui::Render();
	//CRenderer::GetDeviceContext()->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
	//CRenderer::GetDeviceContext()->ClearRenderTargetView(g_mainRenderTargetView, (float*)&clear_color);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
