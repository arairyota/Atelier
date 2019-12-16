#include <list>
#include <typeinfo>

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
//Wall* g_Wall;
//Wall* g_WallLeft;
//Wall* g_WallFront;

void CManager::Init()
{
	CAudioClip::Init();
	CInput::Init();

	CRenderer::Init();

	CoInitializeEx(0, COINIT_MULTITHREADED);
	
	CManager::SetScene<GameScene>();

	

	
}

void CManager::Uninit()
{
	CoUninitialize();

	_Scene->Uninit();
	delete _Scene;

	/*g_Wall->Uninit();
	g_WallLeft->Uninit();
	g_WallFront->Uninit();
*/

	



	CRenderer::Uninit();
	
	/*g_Polygon1->Uninit();
	
	for (int cnt = 0; cnt < 2; cnt++) {
		g_Polygon[cnt]->Uninit();
		delete g_Polygon[cnt];
	}*/
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

//template <typename T>
//void CManager::SetScene()

