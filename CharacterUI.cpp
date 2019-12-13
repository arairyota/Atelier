#include "main.h"

#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "TextureManager.h"
#include "gameActor.h"
#include "polygon.h"
#include "Gauge.h"
#include "CharacterUI.h"
#include "scene.h"

CharacterUI::CharacterUI()
{
	
	

}

void CharacterUI::Init()
{
	_position = XMFLOAT2(0.0f, 0.0f);
	_rotation = XMFLOAT2(0.0f, 0.0f);
	_scale = XMFLOAT2(1.0f, 1.0f);
	_world = XMMatrixIdentity();
}

void CharacterUI::Update()
{
	if (_actor == nullptr) return;
	_hp = _actor->GetLife();
	if (_hp < 0) _hp = 0;
}

void CharacterUI::Set(GameActor* player)
{
	_actor = player;
	_position = XMFLOAT2(600.0f, 900.0f);
	_rotation = XMFLOAT2(0.0f, 0.0f);
	_scale = XMFLOAT2(1.0f, 1.0f);
	_world = XMMatrixIdentity();
	_world *= XMMatrixScaling(_scale.x, _scale.y, 1.0f);
	_world *= XMMatrixTranslation(_position.x, _position.y, 0.0f);
	_hp = player->GetLife();

	Scene* scene = CManager::GetScene();
	_base = scene->AddGameObject<CPolygon>(TYPE_WIDGET);
	_base->Set(XMFLOAT2(50.0f, 0.0f), XMFLOAT2(0.0f, 0.0f), XMFLOAT2(1.0f, 1.0f), _world, TextureManager::GetInstance()->GetTexture(CHAR_UI_BASE));
	//
	//_characterIcon = scene->AddGameObject<CPolygon>(TYPE_WIDGET);
	//_characterIcon->Set(XMFLOAT2(0.0f, 0.0f), XMFLOAT2(0.0f, 0.0f), XMFLOAT2(1.0f, 1.0f), _world, nullptr);
	//
	//_hpIcon = scene->AddGameObject<CPolygon>(TYPE_WIDGET);
	//_hpIcon->Set(XMFLOAT2(0.0f, 0.0f), XMFLOAT2(0.0f, 0.0f), XMFLOAT2(1.0f, 1.0f), _world, nullptr);
	//
	//_mpIcon = scene->AddGameObject<CPolygon>(TYPE_WIDGET);
	//_mpIcon->Set(XMFLOAT2(0.0f, 0.0f), XMFLOAT2(0.0f, 0.0f), XMFLOAT2(1.0f, 1.0f), _world, nullptr);

	_hpGauge = scene->AddGameObject<Gauge>(TYPE_WIDGET);
	_hpGauge->Set(_world, &_hp, true);

	_base->SetDrawFlag(true);


	//_mpGauge = scene->AddGameObject<CPolygon>(TYPE_WIDGET);
	//_mpGauge->Set(XMFLOAT2(0.0f, 0.0f), XMFLOAT2(0.0f, 0.0f), XMFLOAT2(1.0f, 1.0f), _world, nullptr);

}