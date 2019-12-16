#include "main.h"
#include <list>
#include <vector>
#include "renderer.h"
#include "manager.h"

#include "TextureManager.h"
#include "audio_clip.h"
#include "input.h"
#include "GameObject.h"
#include "gameActor.h"
#include "object2D.h"
#include "ItemManager.h"
#include "DamegeNumEffectFactory.h"
#include "polygon.h"
#include "Timer.h"
#include "Flag.h"
#include "gameActor.h"
#include "scene.h"

#include "TitleScene.h"
#include "ResultScene.h"
#include "camera.h"
#include "MeshField.h"
#include "Town.h"
#include "player.h"
#include "enemy.h"
#include "playerInterface.h"
#include "ActionPhase.h"
#include "SortTurn.h"
#include "ItemPoach.h"
#include "OriBomd.h"
#include "GameScene.h"


 std::list<GameActor*>SortTurn::_GameActor;

 static const CHARACTER_STATS puni = CHARACTER_STATS(100.0f, 1.0f, 100.0f, 35.0f, 0.0f, 10.0f);
 static const CHARACTER_STATS araisan = CHARACTER_STATS(300.0f, 300.0f, 300.0f, 53.0f, 0.0f, 20.0f);


GameScene::GameScene()
{
}


GameScene::~GameScene()
{
}

void GameScene::Init()
{
	TextureManager::Create();
	DamegeNumEffectFactory::CreateInstance();
	Timer::Init();
	Flag::Init();
	ItemManager::Create();
	ItemManager::GetInstance()->AllLoad();
	//_bgm = new CAudioClip;
	//_bgm->Load("asset/BGM/HibariKochi.wav"); //wavのみ
	//_bgm->Play(true);
	CCamera* camera = AddGameObject<CCamera>(TYPE_CAMERA);
	MeshField* Field = AddGameObject<MeshField>(TYPE_FIELD);
	Town* town = AddGameObject<Town>(TYPE_OBJECT);
	Player* player = AddGameObject<Player>(TYPE_PLAYER);
	Enemy* enemy = AddGameObject<Enemy>(TYPE_ENEMY);
	Enemy* enemy1 = AddGameObject<Enemy>(TYPE_ENEMY);
	playerInterface* _playerInterface = AddGameObject<playerInterface>(TYPE_WIDGET);
	ItemPoach* itemPoach = AddGameObject<ItemPoach>(TYPE_WIDGET);

	Field->Set(INIT_SIZE_X, INIT_SIZE_Z, INIT_GRID_NUM_X, INIT_GRID_NUM_Z);
	player->Set(XMFLOAT3(0.0f, 20.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(5.0f, 5.0f, 5.0f), araisan);
	enemy->Set(XMFLOAT3(-20.0f, 5.0f, 100.0f), XMFLOAT3(0.0f, 3.14 / 2, 0.0f), XMFLOAT3(10.0f, 10.0f, 10.0f), puni);
	enemy1->Set(XMFLOAT3(20.0f, 5.0f, 100.0f), XMFLOAT3(0.0f, 3.14 / 2, 0.0f), XMFLOAT3(10.0f, 10.0f, 10.0f), puni);
	_playerInterface->Set();
	town->Set(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(7.0f, 7.0f, 7.0f));

	SortTurn::SetActor(player);
	SortTurn::SetActor(enemy);
	SortTurn::SetActor(enemy1);

	SortTurn::Sort();
}

void GameScene::Uninit()
{
	//_bgm->Stop();
	//_bgm->Unload();
	//delete _bgm;

	SortTurn::AllDestory();

	TextureManager::GetInstance()->AllUnLoad();
	TextureManager::Derete();

	Scene::Uninit();
	Timer::Uninit();

	DamegeNumEffectFactory::Delete();

	ItemManager::GetInstance()->AllUnLoad();
	ItemManager::Delete();
}

void GameScene::Update()
{
	Timer::Update();
	SortTurn::BeginTurn();

	Scene::Update();
	ActionPhase::Update();

	if (CInput::GetKeyTrigger('P')) {
		int a = 0; //デバッグ
	}

	if (CInput::GetKeyTrigger(VK_SPACE)) {
		CManager::SetScene<ResultScene>();
	}
	
}
