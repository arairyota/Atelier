#include <string>
#include <list>
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "camera.h"
#include "CameraData.h"
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

	// �E�C���h�E�̕\��(�����������̌�ɍs��)
	ShowWindow(GetWindow(), SW_SHOWDEFAULT);
	UpdateWindow(GetWindow());
}

void CamearEditor::Uninit()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	//for (auto i : _cameraDataList) {
	//	i->Uninit();
	//}
}

void CamearEditor::Update()
{
	//ImGuiIO::MousePos()
}

void CamearEditor::Draw()
{
	//�蔲���錾
	std::string textName = "AddButton";
	ImVec2 buttonSize = ImVec2(10.0f, 10.0f);
	float f = 0.5f;
	static int listbox_item_current = 1;
	
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	//if (_show_demo_window) {
	//	ImGui::ShowDemoWindow(&_show_demo_window);
	//}

	//imgui���j���[�o�[��`
	{
		ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(400, 500), ImGuiCond_Once);
		ImGui::Begin("CameraEditor", nullptr, ImGuiWindowFlags_MenuBar);
	}

	ImGui::SliderFloat("cameraPositionX", &f, 0.0f, 1.0f);
	ImGui::SliderFloat("cameraPositionY", &f, 0.0f, 1.0f);
	ImGui::SliderFloat("cameraPositionZ", &f, 0.0f, 1.0f);

	if (ImGui::Button(textName.c_str())) {
		_cameraDataList.push_back(CManager::GetScene()->AddGameObject<CameraData>(TYPE_OBJECT));
	}

	if (ImGui::CollapsingHeader("CameraPosList")){
		UINT cnt = 0;
		for (auto i : _cameraDataList) {
			if (ImGui::Button("WayPoint")) {
				float x = i->GetPosition().x;
				float y = i->GetPosition().y;
				float z = i->GetPosition().z;

				CManager::GetScene()->GetGameObject<CCamera>(TYPE_CAMERA)->SetCameraPosition(i->GetPosition());
				ImGui::InputFloat("PositionX", &x);
				ImGui::InputFloat("PositionY", &y);
				ImGui::InputFloat("PositionZ", &z);
			}
			cnt++;
		}
	}

	ImGui::End();

	////imgui���j���[�o�[��`
	//{
	//	ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Once);
	//	ImGui::SetNextWindowSize(ImVec2(320, 100), ImGuiCond_Once);
	//	ImGui::Begin("Camera", nullptr, ImGuiWindowFlags_MenuBar);
	//}
	//ImGui::End();



	// Renderin
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
