#include <string>
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
	//ImGuiIO::MousePos()
}

void CamearEditor::Draw()
{
	//手抜き宣言
	std::string textName = "AddButton";
	ImVec2 buttonSize = ImVec2(10.0f, 10.0f);
	float f = 0.5f;
	

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	//if (_show_demo_window) {
	//	ImGui::ShowDemoWindow(&_show_demo_window);
	//}

	//imguiメニューバー定義
	{
		ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(320, 500), ImGuiCond_Once);
		ImGui::Begin("CameraEditor", nullptr, ImGuiWindowFlags_MenuBar);
	}

	ImGui::SliderFloat("cameraPositionX", &f, 0.0f, 1.0f);
	ImGui::SliderFloat("cameraPositionY", &f, 0.0f, 1.0f);
	ImGui::SliderFloat("cameraPositionZ", &f, 0.0f, 1.0f);

	if (ImGui::Button(textName.c_str())) {
		
	}

	ImGui::End();

	//imguiメニューバー定義
	{
		ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(320, 100), ImGuiCond_Once);
		ImGui::Begin("CameraEditor", nullptr, ImGuiWindowFlags_MenuBar);
	}

	for (UINT cnt = 0; cnt < 10; cnt++) {
		ImGui::Text("%d", cnt);
	}

	ImGui::End();

	// Renderin
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
