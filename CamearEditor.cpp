#include <string>
#include <list>
#include <iostream>
#include <fstream>
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "model.h"
#include "camera.h"
#include "CameraData.h"
#include "Flag.h"
#include "MeshField.h"
#include "CamearEditor.h"

#include "scene.h"

using namespace std;

static int selectMode = 0;
static int selectGameMode = 0;

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
	_camera = CManager::GetScene()->GetGameObject<CCamera>(TYPE_CAMERA);
	DefaultCameraDataInit();
	Flag::SetGamePhase(FLAG_INIT);
	_selectData = new SelectData;
	_isEnable = true;
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
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	EditorModeMenu();
	
	if (_isEnable) {
		EditorMenu();
		FileMenu();
		OperationMenu();
		PresetMenu();
		ReservationErase();
		
	}

	// Renderin
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void CamearEditor::Save()
{
	if (_cameraDataList.size() == 0) return;

	std::string name = "CameraData/";

	std::string name2 = "skill.bin";

	std::string a = name + name2;

	FILE* fp = fopen(a.c_str(), "wb");

	if (fp == nullptr) {
		assert(!fp);
	}

	int size = _cameraDataList.size();
	
	fwrite(&size, sizeof(int), 1, fp);
	for (auto i : _cameraDataList) {
		
		fwrite(i, sizeof(CameraData), 1, fp);
	}
	
	fclose(fp);

	/*
	ofstream fout("SampleCameraWork.bin", ios::binary | ios::out);

	//fout.open("SampleCameraWork.bin", ios::binary);

	if (!fout) {
		cout << "ファイル file.txt が開けません";
		return ;
	}
	//ofs.write(reinterpret_cast<char*>(&vec_out[0]), sizeof(int)* size);

	fout.write(reinterpret_cast<char*>(&size), sizeof(int));
	fout.write(reinterpret_cast<char*>(_cameraDataList.front()), sizeof(CameraData) * size);

	fout.close();
	*/
}

void CamearEditor::DataClear()
{
	if(_selectData->_data != nullptr)
		_selectData->_data->GetModel()->SetEnable(true);

	_selectData->_data = nullptr;
	_selectData->_it = _cameraDataList.begin();

	_camera->SetCameraPosition(_defaultCamera->GetPosition());
	_camera->SetQuaternion(_camera->GetTransQuaternion(), _defaultCamera->GetQuaternion());

	for (auto i : _cameraDataList)
	{
		i->SetDestroy();
	}
	_cameraDataList.clear();
}

void CamearEditor::DefaultCameraDataInit()
{
	_defaultCamera = new CameraData;
	_defaultCamera->SetPosition(_camera->GetPosition());
	_defaultCamera->SetQuaternion(*_camera->GetTransQuaternion());
}

void CamearEditor::EditorModeMenu()
{
	//imguiメニューバー定義
	{
		ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(400, 100), ImGuiCond_Once);
		ImGui::Begin("EditorMode", nullptr, ImGuiWindowFlags_MenuBar);

		//操作ツールのmode切り替え
		{
			if (ImGui::RadioButton("EditorMode", &selectGameMode, 0)) {
				_isEnable = true;
				Flag::SetGamePhase(FLAG_INIT);
				CManager::GetScene()->GetGameObject<MeshField>(TYPE_FIELD)->SetDrawing(false);
			}

			if (ImGui::RadioButton("GameMode", &selectGameMode, 1)) {
				_isEnable = false;
				Flag::SetGamePhase(FLAG_ACTION_SELECT);
				CManager::GetScene()->GetGameObject<MeshField>(TYPE_FIELD)->SetDrawing(true);
			}
		}

		ImGui::End();
	}
}

void CamearEditor::EditorMenu()
{
	//imguiメニューバー定義
	{
		ImGui::SetNextWindowPos(ImVec2(10, 100), ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(400, 400), ImGuiCond_Once);
		ImGui::Begin("CameraEditor", nullptr, ImGuiWindowFlags_MenuBar);


		if (ImGui::Button("DefaultCamera")) {
			if (_selectData->_data != nullptr) {
				_selectData->_data->GetModel()->SetEnable(true);
				_selectData->_data = nullptr;
				_selectData->_it = _cameraDataList.begin();
			}

			_camera->SetCameraPosition(_defaultCamera->GetPosition());
			_camera->SetQuaternion(_camera->GetTransQuaternion(), _defaultCamera->GetQuaternion());
		}

		//addButton押したら
		if (ImGui::Button("AddButton")) {
			_cameraDataList.push_back(CManager::GetScene()->AddGameObject<CameraData>(TYPE_OBJECT));
		}

		if (ImGui::Button("DeleteButton")) {
			if (_selectData->_data != nullptr) {
				_selectData->_data->SetDestroy();
				_selectData->_isDelete = true;
				_camera->SetCameraPosition(_defaultCamera->GetPosition());
				_camera->SetQuaternion(_camera->GetTransQuaternion(), _defaultCamera->GetQuaternion());
			}
		}

		if (ImGui::Button("play")) {
			_camera->SetCameraData(_cameraDataList);
			if (_selectData->_data != nullptr) {
				_selectData->_data->SetQuaternion(*_camera->GetTransQuaternion());
				_selectData->_data->GetModel()->SetEnable(true);
			}
			_selectData->_data = nullptr;
			_selectData->_it = _cameraDataList.begin();
		}

		int cnt = 0;

		auto _it = _cameraDataList.begin();

		if (ImGui::CollapsingHeader("CameraPosList")) {
			for (auto i : _cameraDataList) {
				//i->GetModel()->SetEnable(true);
				std::string s = "WayPoint";
				s += std::to_string(cnt);

				if (ImGui::Button(s.c_str())) {
					if (_selectData->_data != nullptr) {
						_selectData->_data->SetQuaternion(*_camera->GetTransQuaternion());
						_selectData->_data->GetModel()->SetEnable(true);
						
					}

					_selectData->_data = i;
					_selectData->_it = _it;
					_selectData->_data->GetModel()->SetEnable(false);

					_camera->SetCameraPosition(_selectData->_data->GetPosition());
					_camera->SetQuaternion(_camera->GetTransQuaternion(), _selectData->_data->GetQuaternion());

				}
				cnt++;
				++_it;
			}
		}

		ImGui::End();
	}
}

void CamearEditor::FileMenu()
{
	//imguiメニューバー定義
	{
		ImGui::SetNextWindowPos(ImVec2(10, 500), ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(400, 500), ImGuiCond_Once);
		ImGui::Begin("File", nullptr, ImGuiWindowFlags_MenuBar);

		//セーブ
		{
			ImGui::InputTextWithHint("FileName", "Please enter a file name", _fileName, 64, ImGuiInputTextFlags_CharsNoBlank);

			if (ImGui::Button("Save")) {
				if (_selectData->_data != nullptr) {
					_selectData->_data->SetQuaternion(*_camera->GetTransQuaternion());
					_selectData->_data->GetModel()->SetEnable(true);
				}

				std::string s = _fileName;
				if (s.size() != 0) {
					Save();
					//_camera->SetCameraData(_cameraDataList);
					_selectData->_data = nullptr;
				}
			}
		}
		ImGui::End();
	}
}

void CamearEditor::OperationMenu()
{
	//imguiメニューバー定義
	{
		ImGui::SetNextWindowPos(ImVec2(1500, 10), ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(400, 500), ImGuiCond_Once);
		ImGui::Begin("CameraPosition", nullptr, ImGuiWindowFlags_MenuBar);


		//操作ツールのmode切り替え
		{
			ImGui::RadioButton("FreeMode", &selectMode, 0);
			ImGui::RadioButton("SliderMode", &selectMode, 1);
		}

		{
			if (ImGui::Button("AllFalse")) {
				for (auto b : _cameraDataList) {
					b->GetModel()->SetEnable(false);
				}
			}

			if (ImGui::Button("AllTrue")) {
				for (auto b : _cameraDataList) {
					b->GetModel()->SetEnable(true);
				}
			}
		}

		//操作ツール系描画
		{
			if (_selectData->_data != nullptr) {
				//切り替え処理
				float p[3];
				int f;
				if (selectMode == 0) {
					p[0] = CManager::GetScene()->GetGameObject<CCamera>(TYPE_CAMERA)->GetPosition().x;
					p[1] = CManager::GetScene()->GetGameObject<CCamera>(TYPE_CAMERA)->GetPosition().y;
					p[2] = CManager::GetScene()->GetGameObject<CCamera>(TYPE_CAMERA)->GetPosition().z;

					f = _selectData->_data->GetFrame();
				}

				if (selectMode == 1) {
					p[0] = *_selectData->_data->GetPositionX();
					p[1] = *_selectData->_data->GetPositionY();
					p[2] = *_selectData->_data->GetPositionZ();
				}

				ImGui::InputFloat("PositionX", &p[0], 0.01f, 10.0f, "%.3f");
				ImGui::InputFloat("PositionY", &p[1], 0.01f, 10.0f, "%.3f");
				ImGui::InputFloat("PositionZ", &p[2], 0.01f, 10.0f, "%.3f");

				ImGui::InputInt("SetFrame", &f);
				//_dataに返す
				{
					_selectData->_data->SetPosition(p[0], p[1], p[2]);
					_selectData->_data->SetFrame(f);
					_camera->SetCameraPosition(_selectData->_data->GetPosition());
				}
				_selectData->_data->GetModel()->SetEnable(false);
			}
		}
		ImGui::End();
	}
}

void CamearEditor::PresetMenu()
{
	//imguiメニューバー定義
	{
		ImGui::SetNextWindowPos(ImVec2(1500, 500), ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(400, 500), ImGuiCond_Once);
		ImGui::Begin("Preset", nullptr, ImGuiWindowFlags_MenuBar);
		if (ImGui::Button("Sample1")) {
			FILE* fp = fopen("CameraData/SampleCameraWork.bin", "rb");

			int size;
			fread(&size, sizeof(int), 1, fp);

			DataClear();

			//_listv.clear();
			//_listv.resize(size);

			//for (int i = 0; i < size; i++) {
			//	_listv.push_back(new CameraData);
			//}

			//_listv.reserve(size);

			fread(&_listv[0], sizeof(CameraData), 1, fp);
			fread(&_listv[1], sizeof(CameraData), 1, fp);
			fread(&_listv[2], sizeof(CameraData), 1, fp);

			//int b = _cameraDataList.size(); //デバッグ用

			for (int cnt = 0; cnt < size; cnt++) {
				CameraData* data = CManager::GetScene()->AddGameObject<CameraData>(TYPE_OBJECT);
				_cameraDataList.push_back(data);
				data->SetCameraData(_listv[cnt]); //読み込んだデータを入れる
			}
			int a = _cameraDataList.size(); //デバッグ
		}

		if (ImGui::Button("Sample2")) {
			FILE* fp = fopen("CameraData/test.bin", "rb");

			int size;
			fread(&size, sizeof(int), 1, fp);

			DataClear();

			//_listv.resize(size);
			//_listv.reserve(size);

			fread(&_listv[0], sizeof(CameraData), 1, fp);
			fread(&_listv[1], sizeof(CameraData), 1, fp);
			fread(&_listv[2], sizeof(CameraData), 1, fp);
			fread(&_listv[3], sizeof(CameraData), 1, fp);
			fread(&_listv[4], sizeof(CameraData), 1, fp);

			//int b = _cameraDataList.size(); //デバッグ用

			for (int cnt = 0; cnt < size; cnt++) {
				CameraData* data = CManager::GetScene()->AddGameObject<CameraData>(TYPE_OBJECT);
				_cameraDataList.push_back(data);
				data->SetCameraData(_listv[cnt]); //読み込んだデータを入れる
			}
			int a = _cameraDataList.size(); //デバッグ
		}

		ImGui::End();
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: ReservationErase
//戻り値	: 
//説明		: 消去予約したデータをいっぺんに消去
//引数		:
//////////////////////////////////////////////////////////////////////////////
void CamearEditor::ReservationErase()
{
	if (_selectData->_isDelete) {
		auto it = _cameraDataList.begin();
		for (it; it != _cameraDataList.end();) {
			if (_selectData->_it == it) {
				it = _cameraDataList.erase(it);
				_selectData->_isDelete = false;
				_selectData->_data = nullptr;
				//_selectData->_it = _cameraDataList.begin();
				return;
			}
			++it;
		}
		
	}
}
