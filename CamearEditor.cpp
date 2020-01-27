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

static int selectMode = 0;

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
	//_camera = new CCamera;
	_camera = CManager::GetScene()->GetGameObject<CCamera>(TYPE_CAMERA);
	DefaultCameraDataInit();
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
		
		_camera->SetCameraPosition(_defaultCamera->GetPosition());
		_camera->SetQuaternion(_camera->GetTransQuaternion(), _defaultCamera->GetQuaternion());
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
				if (_data != nullptr) {
					_data->SetQuaternion(*_camera->GetTransQuaternion());
				}

				_data = i;
				
				_camera->SetCameraPosition(_data->GetPosition());
				_camera->SetQuaternion(_camera->GetTransQuaternion(), _data->GetQuaternion());
				
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

	//操作ツールのmode切り替え
	{
		ImGui::RadioButton("FreeMode", &selectMode, 0);
		ImGui::RadioButton("SliderMode", &selectMode, 1); 
	}

	//操作ツール系描画
	{
		if (_data != nullptr) {
			//切り替え処理
			float p[3];
			if (selectMode == 0) {
				p[0] = CManager::GetScene()->GetGameObject<CCamera>(TYPE_CAMERA)->GetPosition().x;
				p[1] = CManager::GetScene()->GetGameObject<CCamera>(TYPE_CAMERA)->GetPosition().y;
				p[2] = CManager::GetScene()->GetGameObject<CCamera>(TYPE_CAMERA)->GetPosition().z;
			}

			if (selectMode == 1) {
				p[0] = *_data->GetPositionX();
				p[1] = *_data->GetPositionY();
				p[2] = *_data->GetPositionZ();
			}

			
			ImGui::InputFloat("PositionX", &p[0], 0.01f, 10.0f, "%.3f");
			ImGui::InputFloat("PositionY", &p[1], 0.01f, 10.0f, "%.3f");
			ImGui::InputFloat("PositionZ", &p[2], 0.01f, 10.0f, "%.3f");
			//_dataに返す
			{
				_data->SetPosition(p[0], p[1], p[2]);
				_camera->SetCameraPosition(_data->GetPosition());
			}
			_data->GetModel()->SetEnable(false);
		}
	}
	ImGui::End();

	// Renderin
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void CamearEditor::DefaultCameraDataInit()
{
	_defaultCamera = new CameraData;
	_defaultCamera->SetPosition(_camera->GetPosition());
	_defaultCamera->SetQuaternion(*_camera->GetTransQuaternion());
}
