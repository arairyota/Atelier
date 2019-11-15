#include "main.h"
#include <list>
#include <vector>
#include "renderer.h"
#include "GameObject.h"
#include "scene.h"
#include "manager.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "input.h"
#include "audio_clip.h"

#include "TitleScene.h"



TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{
}

void TitleScene::Uninit()
{
	Scene::Uninit();
}

void TitleScene::Update()
{
	Scene::Update();
	if (CInput::GetKeyTrigger(VK_SPACE)) {
		CManager::SetScene<GameScene>();
	}
}
