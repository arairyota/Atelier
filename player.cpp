#include "main.h"


#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "GameObject.h"
#include "object3D.h"
#include "gameActor.h"

#include "Flag.h"
#include "SortTurn.h"
#include "ItemBase.h"
#include "ItemPoach.h"
#include "camera.h"
#include "CameraData.h"
#include "ModelAnimation.h"
#include "MeshField.h"
#include "player.h"
#include "enemy.h"
#include "model.h"
#include "DamegeNumEffect.h"
#include "BattleJudg.h"
#include "CharacterUI.h"
#include "scene.h"

void Player::Init()
{
	_position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	_rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	_scale    = XMFLOAT3(0.0f, 0.0f, 0.0f);

	_model = nullptr;

	_stats._waitTime = _stats._spd;

	//_model->Load("asset/miku_01.obj");

	_cameraList.clear();
}

void Player::Uninit()
{
	//_model->Unload();
	
	CManager::GetScene()->DestroyGameObject(_charaUI);

	_testModel->Unload();
}

void Player::Update()
{
	Scene* scene = CManager::GetScene();
	MeshField* field = scene->GetGameObject<MeshField>(TYPE_FIELD);
	/*
	if (CInput::GetKeyPress('A')) {
		_mtxRotationY = XMMatrixRotationY( -XMConvertToRadians(ROTASION_SPEED));
		_front = XMVector3TransformNormal(_front, _mtxRotationY);
		_right = XMVector3TransformNormal(_right, _mtxRotationY);
		_rotation.y -= XMConvertToRadians(ROTASION_SPEED);
	}

	if (CInput::GetKeyPress('D')) {
		_mtxRotationY = XMMatrixRotationY( XMConvertToRadians(ROTASION_SPEED));
		_front = XMVector3TransformNormal(_front, _mtxRotationY);
		_right = XMVector3TransformNormal(_right, _mtxRotationY);
		_rotation.y += XMConvertToRadians(ROTASION_SPEED);
	}

	if (CInput::GetKeyPress('W')) {
		_position.x += XMVectorGetX(_front) * PLAYER_SPEED;
		_position.y += XMVectorGetY(_front) * PLAYER_SPEED;
		_position.z += XMVectorGetZ(_front) * PLAYER_SPEED;
	
		_position.y = 10.0f;
	}
	*/
	if (CInput::GetKeyTrigger('L')) {
		int a = 0;

		/*Bullet* bullet = scene->AddGameObject<Bullet>(3);
		bullet->Init();
		bullet->Creat(_position, _rotation, _scale, _front, _right, _up, 100);*/
	}
	

	_position.y = field->GetHeight(_position) + 0.0f;
}

void Player::Draw()
{
	// マトリクス設定
	XMMATRIX world;
	world = XMMatrixScaling(_scale.x, _scale.y, _scale.z);
	world *= XMMatrixRotationRollPitchYaw(_rotation.x, _rotation.y, _rotation.z);
	world *= XMMatrixTranslation(_position.x, _position.y, _position.z);
	CRenderer::SetWorldMatrix(&world);

	//_model->Draw();
	_testModel->Draw(world);
}

void Player::Set(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scale, CHARACTER_STATS stats)
{
	Scene* scene = CManager::GetScene();

	_position = pos;
	_rotation = rot;
	_scale = scale;

	_stats = stats;

	//_model = new CModel;	
	//_model->Load("asset/miku_01.obj");

	_testModel = new ModelAnimation;
	_testModel->Load();

	_cameraPosition.x = _position.x + 10.0f;
	_cameraPosition.y = _position.y + 20.0f;
	_cameraPosition.z = _position.z - 60.0f;

	_charaUI = scene->AddGameObject<CharacterUI>(TYPE_WIDGET);
	_charaUI->Set(this);
}

void Player::InitAnimData()
{
	_atkAnimData.is_Finish = false; 
	_atkAnimData.startFlame = 0.0f;
	_atkAnimData.nowFlame = 0.0f;
	_atkAnimData.cameraPosition.x = this->GetPosition().x + 50.0f;
	_atkAnimData.cameraPosition.y = this->GetPosition().y + 50.0f;
	_atkAnimData.cameraPosition.z = this->GetPosition().z - 50.0f;

}

void Player::FirstAction()
{
	Flag::SetGamePhase(FLAG_ACTION_SELECT);
	
}

void Player::Attack()
{
	auto enemys = SortTurn::GetGameActorList<Enemy>();
	if (SortTurn::GetGameActorList<Enemy>().front() == nullptr) return;
	for (auto* enemy : enemys) {
		if (enemy->GetGameActor()->_stats._isHit) {
			//初期化
			if (_atkAnimData.nowFlame == 0) {
				XMFLOAT3 that = enemy->GetPosition();
				_len.x = that.x - this->_position.x;
				_len.z = that.z - this->_position.z;
				_len.x /= (float)90;
				_len.z /= (float)90;
				//DamegeNumEffect* Damege = CManager::GetScene()->AddGameObject<DamegeNumEffect>(TYPE_EFFECT);
				//Damege->Set(this->_position, 5);
			}

			//90フレームになるまでやる
			if (_atkAnimData.nowFlame < 90) {
				this->_position.x += _len.x;
				this->_position.z += _len.z;
			}

			if (_atkAnimData.nowFlame == 90) {
				enemy->_stats._life -= BattleJudg::DamageJudg(this->_stats._atk, enemy->_stats._def, _position);
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
				Flag::SetTurnLoopFlag(false);
			}

			_atkAnimData.nowFlame++;

			if (_atkAnimData.is_Finish) {
				this->InitAnimData();

				enemy->SetHit(false);
				this->_stats._nowTurn = false;
				Flag::SetTurnLoopFlag(false);

				if (BattleJudg::IsDeath(enemy->_stats._life)) {
					CManager::GetScene()->DestroyGameObject(enemy);
					SortTurn::Sort();
					if (BattleJudg::IsClear(SortTurn::GetGameActorList<Enemy>().size())) return;
					
				}
				//this->InitAnimData();
				//
				//enemy->SetHit(false);
				//this->_stats._nowTurn = false;
				//Flag::SetTurnLoopFlag(false);
			}
		}
	}
}

void Player::Action()
{
	Scene* scene = CManager::GetScene();
	if (Flag::GetSelectAction() == FLAG_ATTACK_SELECT) {
		this->Attack();
	}

	if (Flag::GetSelectAction() == FLAG_ITEM_SELECT) {
		ItemBase* item = scene->GetGameObject<ItemPoach>(TYPE_WIDGET)->GetSelectItem();
		item->Use(_position, this);
	}

	if (Flag::GetSelectAction() == FLAG_SKILL_SELECT) {
		//アニメーション再生
		if (_isFirst) { 
			_testModel->ChangeAnimation(1); 
			_animFrame = 0;
			_isFirst = false;

			SetActionCamera();
		}
		if (_animFrame > 170) {
			Flag::SetGamePhase(FLAG_ACTION_SELECT);
			Flag::SetSelectAction(FLAG_ACTION_SELECT);
			_testModel->ChangeAnimation(0);
			_isFirst = true;

		}
		++_animFrame;
	}
}

XMFLOAT3 Player::GetCameraPosition()
{
	return _cameraPosition;
}

void Player::SetActionCamera()
{
	_cameraList.clear();
	
	FILE* fp = fopen("CameraData/skill.bin", "rb");

	//ifstream ifs("SampleCameraWork.bin", ios::binary | ios::in);

	int size;
	fread(&size, sizeof(int), 1, fp);
	for (int cnt = 0; cnt < size; cnt++) {

		fread(&_cameraListv[cnt], sizeof(CameraData), 1, fp);
	}

	fclose(fp);
	//int b = _cameraDataList.size(); //デバッグ用

	for (int cnt = 0; cnt < size; cnt++) {
		_cameraList.push_back(&_cameraListv[cnt]);
	}

	CManager::GetScene()->GetGameObject<CCamera>(TYPE_CAMERA)->SetCameraData(_cameraList);

	
}
