#include "main.h"
#include <list>
#include <vector>
#include "renderer.h"
#include "GameObject.h"
#include "scene.h"
#include "manager.h"
#include "TitleScene.h"
#include "input.h"
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
