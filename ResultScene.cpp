#include "main.h"
#include <list>
#include <vector>
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "GameObject.h"
#include "scene.h"
#include "TitleScene.h"

#include "audio_clip.h"
#include "ResultScene.h"





ResultScene::ResultScene()
{
}


ResultScene::~ResultScene()
{
}

void ResultScene::Init()
{
}

void ResultScene::Uninit()
{
}

void ResultScene::Update()
{
	Scene::Update();
	if (CInput::GetKeyTrigger(VK_SPACE)) {
		CManager::SetScene<TitleScene>();
	}
}
