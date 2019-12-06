#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "gameActor.h"
#include "input.h"
#include "model.h"
#include "camera.h"
#include "player.h"
#include "enemy.h"
#include "scene.h"
#include "Flag.h"
#include "SortTurn.h"
#include "ItemPoach.h"
#include "TargetSelect.h"


TargetSelect::TargetSelect()
{
}


TargetSelect::~TargetSelect()
{
}

void TargetSelect::Init()
{
	_position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	_rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	_scale= XMFLOAT3(0.0f, 0.0f, 0.0f);
	_model = new CModel;
	_model->Load("asset/TargetSelect.obj");
}

void TargetSelect::Uninit()
{
	this->SetDestroy();
	//_model->Unload();
	//delete _model;
}

void TargetSelect::Update()
{
		if (_isFirst) {
			Scene* scene = CManager::GetScene();
			GameActor* player = SortTurn::GetGameActorFront();
			CCamera* camera = scene->GetGameObject<CCamera>(TYPE_CAMERA);
			camera->Set(player->GetCameraPosition(), XMFLOAT3(-20.0f, 5.0f, 100.0f));
			_isFirst = false;
			//camera->Set(XMFLOAT3(10, 20, -20), _ENEMYPOSITION);
		}
		
		if (CInput::GetKeyTrigger('A')) {
			if (_select > 0) {
				_select--;
			}
		}

		if (CInput::GetKeyTrigger('D') ){
			if (_select < _enemyMax - 1) {
				_select++;
			}
		}

		
		if (_enemy != nullptr) {
			_position = _enemys[_select]->GetPosition();
			_position.y = 20.0f;
		}
		
		if (CInput::GetKeyTrigger('E')) {
			Flag::SetGamePhase(FLAG_ACTION_PHASE);

			//あたり判定内の敵全てのあたったフラグをtrueにする
			_enemys[_select]->SetHit(true);
			_isFirst = true;
			Uninit();
		}

		if (CInput::GetKeyTrigger('Q')) {
			Flag::SetGamePhase(_oldSelectMode);
			ChangePhase();
			CManager::GetScene()->GetGameObject<CCamera>(TYPE_CAMERA)->Init();

			Uninit();
			_isFirst = true;
			CInput::Init();
		}
	}

void TargetSelect::Draw()
{
	// マトリクス設定
	XMMATRIX world;
	world = XMMatrixScaling(_scale.x, _scale.y, _scale.z);
	world *= XMMatrixRotationRollPitchYaw(_rotation.x, _rotation.y, _rotation.z);
	world *= XMMatrixTranslation(_position.x, _position.y, _position.z);
	CRenderer::SetWorldMatrix(&world);

	_model->Draw();
}

void TargetSelect::Set(int oldSelect)
{
	_select = 0;
	_enemyMax = 0;
	_oldSelectMode = oldSelect;

	_enemy = CManager::GetScene()->GetGameObject<Enemy>(TYPE_ENEMY);
	_enemys = CManager::GetScene()->GetGameObjects<Enemy>(TYPE_ENEMY);

	_scale = XMFLOAT3(3.0f, 3.0f, 3.0f);

	//敵が何体いるか数える
	if (_enemy != nullptr) {
		for (Enemy* enemy : _enemys) {
			_enemyMax++;

		}
	}

	//_position = _enemy->GetPosition();
	
}

void TargetSelect::ChangePhase()
{
	Scene* scene = CManager::GetScene();

	if (_oldSelectMode == FLAG_ITEM_SELECT) {
		ItemPoach* itemPoach = scene->AddGameObject<ItemPoach>(TYPE_WIDGET);
		return;
	}

	if (_oldSelectMode == FLAG_SKILL_SELECT) {
		
		return;
	}

	if (_oldSelectMode == FLAG_ATTACK_SELECT)
	{
		return;
	}
}
