#include <list>
#include <typeinfo>

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"


#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "TextureManager.h"
#include "ItemManager.h"
#include "scene.h"
#include "ResultScene.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "input.h"
#include "audio_clip.h"

Scene* CManager::_Scene = nullptr;

void CManager::Init()
{
	CAudioClip::Init();
	CInput::Init();

	CRenderer::Init();

	CoInitializeEx(0, COINIT_MULTITHREADED);
	
	CManager::SetScene<TitleScene>();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(GetWindow());
	ImGui_ImplDX11_Init(CRenderer::GetDevice(), CRenderer::GetDeviceContext());
}

void CManager::Uninit()
{
	CoUninitialize();

	_Scene->Uninit();
	delete _Scene;

	CRenderer::Uninit();

	CInput::Uninit();
	CAudioClip::Uninit();
}

void CManager::Update()
{
	CInput::Update();

	_Scene->Update();
}

void CManager::Draw()
{
	CRenderer::Begin();

	_Scene->Draw();

	CRenderer::End();

}

Scene* CManager::GetScene()
{
	return _Scene;
}