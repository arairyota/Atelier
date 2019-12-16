#include "main.h"
#include <list>
#include <vector>
#include "manager.h"
#include "renderer.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "camera.h"
#include "polygon.h"
#include "MeshField.h"
#include "Town.h"
#include "player.h"
#include "enemy.h"
#include "scene.h"
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

static const CHARACTER_STATS puni = CHARACTER_STATS(100.0f, 1.0f, 100.0f, 35.0f, 0.0f, 10.0f);
static const CHARACTER_STATS araisan = CHARACTER_STATS(300.0f, 300.0f, 300.0f, 123.0f, 0.0f, 20.0f);


void TitleScene::Init()
{
	TextureManager::Create();
	CCamera* camera = AddGameObject<CCamera>(TYPE_CAMERA);
	MeshField* Field = AddGameObject<MeshField>(TYPE_FIELD);
	Town* town = AddGameObject<Town>(TYPE_OBJECT);
	Player* player = AddGameObject<Player>(TYPE_PLAYER);
	Enemy* enemy = AddGameObject<Enemy>(TYPE_ENEMY);
	Enemy* enemy1 = AddGameObject<Enemy>(TYPE_ENEMY);

	

	Field->Set(INIT_SIZE_X, INIT_SIZE_Z, INIT_GRID_NUM_X, INIT_GRID_NUM_Z);
	player->Set(XMFLOAT3(0.0f, 20.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(5.0f, 5.0f, 5.0f), araisan);
	enemy->Set(XMFLOAT3(-20.0f, 5.0f, 100.0f), XMFLOAT3(0.0f, 3.14 / 2, 0.0f), XMFLOAT3(10.0f, 10.0f, 10.0f), puni);
	enemy1->Set(XMFLOAT3(20.0f, 5.0f, 100.0f), XMFLOAT3(0.0f, 3.14 / 2, 0.0f), XMFLOAT3(10.0f, 10.0f, 10.0f), puni);

	town->Set(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(7.0f, 7.0f, 7.0f));
	
	camera->SetCameraPosition(XMFLOAT3(0.0f, 50.0f, -50.0f));
	camera->SetLookQuaternion(camera->GetViewQuaternion(), &enemy->GetPosition());

	CPolygon* TitleLogo = AddGameObject<CPolygon>(TYPE_WIDGET);
	TitleLogo->Set(XMFLOAT2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), XMFLOAT2(0.0f, 0.0f), XMFLOAT2(0.3f, 0.3f), XMMatrixIdentity(), TextureManager::GetInstance()->GetTexture(TITLELOGO));
	TitleLogo->SetDrawFlag(true);
}

void TitleScene::Uninit()
{
	Scene::Uninit();
}

void TitleScene::Update()
{
	Scene::Update();
	if (CInput::GetKeyTrigger('E')) {
		CManager::SetScene<GameScene>();
	}
}
