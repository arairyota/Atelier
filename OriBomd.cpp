#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "SortTurn.h"
#include "Flag.h"
#include "TextureManager.h"
#include "texture.h"
#include "GameObject.h"
#include "object3D.h"
#include "gameActor.h"
#include "player.h"
#include "enemy.h"
#include "camera.h"
#include "BattleJudg.h"
#include "billboard.h"
#include "OriBomd.h"
#include "scene.h"

void OriBomd::Init()
{
	
	_atk = 50.0f; 
	_attribute = Fire;
	_num = 5;

	_Texture = TextureManager::GetInstance()->GetTexture(ORIBOMD);
	

	
	//_polygon = scene->AddGameObject<CPolygon>(TYPE_WIDGET);
	
}

void OriBomd::Uninit()
{
	
}

void OriBomd::Update()
{
	if (Flag::GetGamePhase() == FLAG_ITEM_SELECT) {
		_polygon->SetDrawFlag(true);
	}
	else {
		_polygon->SetDrawFlag(false);
	}
}

void OriBomd::Draw()
{

}

void OriBomd::Use(XMFLOAT3 position, GameActor* user)
{
	Scene* scene = CManager::GetScene();
	XMFLOAT3 pos = position;
	
	if (_isFirst) {
		pos.y = 20.0f;
		_camera = scene->GetGameObject<CCamera>(TYPE_CAMERA);
		_billboard = scene->AddGameObject<Billboard>(TYPE_OBJECT);
		_billboard->Set(pos, _scale, TextureManager::GetInstance()->GetTexture(ORIBOMD));
		_isFirst = false;
		_animFrame = 0;
	}

	auto enemys = SortTurn::GetGameActorList<Enemy>();
	if (SortTurn::GetGameActorList<Enemy>().front() == nullptr) return;
	for (auto* enemy : enemys) {
		if (enemy->GetGameActor()->_stats._isHit) {
			if (_animFrame == 0) {	//������
				//CManager::GetScene()->GetGameObject<CCamera>(TYPE_CAMERA)->SetHoming(XMFLOAT3(pos.x, pos.y+ 10.0f, pos.z + 40.0f) ,pos);
				_camera->SetLookQuaternion(_camera->GetViewQuaternion(), &_position);
				_len.x = enemy->GetPosition().x - _position.x;
				_len.z = enemy->GetPosition().z - _position.z;
				_len.x /= ITEM_SPEED_FRAME;
				_len.z /= ITEM_SPEED_FRAME;
			}

			if (_animFrame == 60) {
				_camera->SetCameraPosition(user->GetCameraPosition());
				_camera->SetLookQuaternion(_camera->GetViewQuaternion(), &_position);
			}

			if (_animFrame < 90 && _animFrame > 180) {
				_position.x -= _len.x;
				_position.y -= _len.y;
			}

			if (_animFrame == 180) {
				_billboard->SetDestroy();
				enemy->_stats._life -= BattleJudg::DamageJudg(_atk, enemy->_stats._def, _position);
			}

			if (_animFrame == 240) {
				user->SetWaitTime(_waitTime);
				enemy->SetHit(false);
				user->_stats._nowTurn = false;
				Flag::SetTurnLoopFlag(false);
				_isFirst = true;
				if (BattleJudg::IsDeath(enemy->_stats._life)) {
					CManager::GetScene()->DestroyGameObject(enemy);
					SortTurn::Sort();
					if (BattleJudg::IsClear(SortTurn::GetGameActorList<Enemy>().size())) return;

				}
			}



			_animFrame++;
		}
	}

}
