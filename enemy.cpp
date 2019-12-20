#include <list>
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "model.h"
#include "Flag.h"
#include "gameActor.h"
#include "SortTurn.h"
#include "ModelAnimation.h"
#include "camera.h"
#include "enemy.h"
#include "player.h"
#include "BattleJudg.h"
#include "scene.h"

void Enemy::Init()
{
	_position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	_rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	_scale    = XMFLOAT3(0.0f, 0.0f, 0.0f);

	/*_position = XMFLOAT3(0.0f, 1.0f, 0.0f);
	_rotation = XMFLOAT3(0.0f, 3.14 / 2, 0.0f);
	_scale = XMFLOAT3(50.0f, 50.0f, 50.0f);*/

	//Load("asset/miku_01.obj");

	_model = nullptr;
	_testModel = new ModelAnimation;
	_testModel->Load("asset/puni1.fbx");

	//_model->Load("asset/miku_01.obj");

	_stats._waitTime = _stats._spd;

	InitAnimData();
}

void Enemy::Uninit()
{
	//_model->Unload();
	_testModel->Unload();
}

void Enemy::Update()
{
	//_rotation.y += 0.2f;

}

void Enemy::Draw()
{
	// マトリクス設定
	XMMATRIX world;
	world = XMMatrixScaling(_scale.x, _scale.y, _scale.z);
	world *= XMMatrixRotationRollPitchYaw(_rotation.x, _rotation.y, _rotation.z);
	world *= XMMatrixTranslation(_position.x, _position.y, _position.z);
	CRenderer::SetWorldMatrix(&world);
	_testModel->Draw(world);
	//_model->Draw();
}

void Enemy::Set(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scale, CHARACTER_STATS stats)
{
	_position = pos;
	_rotation = rot;
	_scale = scale;

	_stats = stats;
	_stats._isHit = false;
	_stats._waitTime = _stats._spd;

	_cameraPosition.x = _position.x - 10.0f;
	_cameraPosition.y = _position.y + 20.0f;
	_cameraPosition.z = _position.z + 60.0f;

	/*_position = XMFLOAT3(0.0f, 1.0f, 0.0f);
	_rotation = XMFLOAT3(0.0f, 3.14 / 2, 0.0f);
	_scale = XMFLOAT3(50.0f, 50.0f, 50.0f);*/

	//Load("asset/miku_01.obj");

	//_model = new CModel;
	//_model->Load("asset/miku_01.obj");
}

void Enemy::Attack()
{
	std::vector<Player*> players = CManager::GetScene()->GetGameObjects<Player>(TYPE_PLAYER);
	if (players.front() == nullptr) return;
	for (Player* player : players) {
		if (player->GetPlayer()->_stats._isHit) {
			//初期化
			if (_atkAnimData.nowFlame == 0) {
				XMFLOAT3 that = player->GetPosition();
				_len.x = that.x - this->_position.x;
				_len.z = that.z - this->_position.z;
				_len.x /= (float)90;
				_len.z /= (float)90;
				CCamera* camera = CManager::GetScene()->GetGameObject<CCamera>(TYPE_CAMERA);
				camera->SetCameraPosition(_cameraPosition);
				camera->SetLookQuaternion(camera->GetViewQuaternion(), &player->GetPosition());
			}

			//90フレームになるまでやる
			if (_atkAnimData.nowFlame < 90) {
				this->_position.x += _len.x;
				this->_position.z += _len.z;
			}

			if (_atkAnimData.nowFlame == 90) {
				player->_stats._life -= BattleJudg::DamageJudg(this->_stats._atk, player->_stats._def, _position);
			}
			
			//90~180まで
			if (_atkAnimData.nowFlame > 90 && _atkAnimData.nowFlame < 180)
			{
				this->_position.x -= _len.x;
				this->_position.z -= _len.z;
			}

			//180フレーム後
			if (_atkAnimData.nowFlame == 180) {
				
				_stats._waitTime += ENEMY_ATTACK_WAIT_TIME;
				//SortTurn::Sort(); //ここで呼ぶ必要なくね？
				_atkAnimData.is_Finish = true;
			}

			_atkAnimData.nowFlame++;

			if(_atkAnimData.is_Finish){
				this->InitAnimData();
				CManager::GetScene()->GetGameObject<CCamera>(TYPE_CAMERA)->Init();
				player->SetHit(false);
				this->_stats._nowTurn = false;
				Flag::SetTurnLoopFlag(false);

				if (BattleJudg::IsDeath(player->_stats._life)) {
					CManager::GetScene()->DestroyGameObject(player);
					SortTurn::Sort();
					if (BattleJudg::IsClear(SortTurn::GetGameActorList<Player>().size())) return;
				}
				
			}
		}
	}
}

void Enemy::FirstAction()
{
	//unsigned short act = (rand() % 3); //どの行動を起こすのか
	//unsigned short selectTarget = (rand() % 3);
	unsigned short act = 0;
	unsigned short selectTarget = 0;

	if (act == 0) {
		_actFlag = ENEMY_ATTACK_FLAG;
		Flag::SetGamePhase(FLAG_ACTION_PHASE);

	}
	std::vector<Player*> players = CManager::GetScene()->GetGameObjects<Player>(TYPE_PLAYER);
	if (players.front() == nullptr) return;
	players[selectTarget]->SetHit(true);
}

void Enemy::Action()
{
	if (_actFlag == ENEMY_ATTACK_FLAG) {
		this->Attack();
	}

	//if (_actFlag == ENEMY_SKILL_FLAG) 
}

void Enemy::InitAnimData()
{
	_atkAnimData.is_Finish = false;
	_atkAnimData.startFlame = 0.0f; 
	_atkAnimData.nowFlame = 0.0f;
	_atkAnimData.cameraPosition.x = this->GetPosition().x - 10.0f;
	_atkAnimData.cameraPosition.y = this->GetPosition().y + 10.0f;
	_atkAnimData.cameraPosition.z = this->GetPosition().z + 10.0f;
}

XMFLOAT3 Enemy::GetCameraPosition()
{
	return _cameraPosition;
}


