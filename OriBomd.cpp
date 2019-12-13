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

void OriBomd::Use(XMFLOAT3 position)
{
	Scene* scene = CManager::GetScene();
	XMFLOAT3 pos = position;
	pos.y = 20.0f;
	if (_isFirst) {
		_billboard = scene->AddGameObject<Billboard>(TYPE_OBJECT);
		_billboard->Set(pos, _scale, TextureManager::GetInstance()->GetTexture(ORIBOMD));
		_isFirst = false;
	}

	auto enemys = SortTurn::GetGameActorList<Enemy>();
	if (SortTurn::GetGameActorList<Enemy>().front() == nullptr) return;
	for (auto* enemy : enemys) {
		if (enemy->GetGameActor()->_stats._isHit) {
			if (_animFrame == 0) {	//‰Šú‰»
				//CManager::GetScene()->GetGameObject<CCamera>(TYPE_CAMERA)->SetHoming(XMFLOAT3(pos.x, pos.y+ 10.0f, pos.z + 40.0f) ,pos);
				CCamera* camera = scene->GetGameObject<CCamera>(TYPE_CAMERA);
				camera->SetLookQuaternion(camera->GetViewQuaternion(), &camera->GetPosition(), &_position);

			}
		}
	}

}
