#include <string>
#include <list>
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "model.h"
#include "camera.h"
#include "CameraData.h"
#include "CamearEditor.h"

#include "scene.h"

#include	<string>

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
	_defaultCamera = new CameraData;
	_defaultCamera->SetPosition(CManager::GetScene()->GetGameObject<CCamera>(TYPE_CAMERA)->GetPosition());
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
	static int listbox_item_current = 1;
	
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	//if (_show_demo_window) {
	//	ImGui::ShowDemoWindow(&_show_demo_window);
	//}

	//imguiメニューバー定義
	{
		ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(400, 500), ImGuiCond_Once);
		ImGui::Begin("CameraEditor", nullptr, ImGuiWindowFlags_MenuBar);
	}

	if (ImGui::Button("DefaultCamera")) {
		_data = nullptr;
		CManager::GetScene()->GetGameObject<CCamera>(TYPE_CAMERA)->SetCameraPosition(_defaultCamera->GetPosition());
	}

	//addButton押したら
	if (ImGui::Button(textName.c_str())) {
		_cameraDataList.push_back(CManager::GetScene()->AddGameObject<CameraData>(TYPE_OBJECT));
	}

	int cnt = 0;
	if (ImGui::CollapsingHeader("CameraPosList")){
		for (auto i : _cameraDataList) {
			i->GetModel()->SetEnable(true);
			std::string s = "WayPoint";
			s += std::to_string(cnt);

			if (ImGui::Button(s.c_str())) {
				
				_data = i;
				//CManager::GetScene()->GetGameObject<CCamera>(TYPE_CAMERA)->SetCameraPosition(i->GetPosition());
				
			}
			cnt++;
		}
	}

	ImGui::End();

	//imguiメニューバー定義
	{
		ImGui::SetNextWindowPos(ImVec2(1500, 10), ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(400, 500), ImGuiCond_Once);
		ImGui::Begin("CameraPosition", nullptr, ImGuiWindowFlags_MenuBar);
	}

	//操作ツール系描画
	{
		if (_data != nullptr) {
			float p[3] = { *_data->GetPositionX(), *_data->GetPositionY(), *_data->GetPositionZ() };
			ImGui::InputFloat("PositionX", &p[0], 0.01f, 10.0f, "%.3f");
			ImGui::InputFloat("PositionY", &p[1], 0.01f, 10.0f, "%.3f");
			ImGui::InputFloat("PositionZ", &p[2], 0.01f, 10.0f, "%.3f");
			//_dataに返す
			{
				_data->SetPosition(p[0], p[1], p[2]);
				CManager::GetScene()->GetGameObject<CCamera>(TYPE_CAMERA)->SetCameraPosition(_data->GetPosition());
			}
			_data->GetModel()->SetEnable(false);
		}
	}
	ImGui::End();



	// Renderin
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
