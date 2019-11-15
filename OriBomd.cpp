#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "Flag.h"
#include "TextureManager.h"
#include "texture.h"
#include "GameObject.h"
#include "object3D.h"
#include "gameActor.h"
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
	_billboard = scene->AddGameObject<Billboard>(TYPE_OBJECT);
	_billboard->Set(position, _scale, TextureManager::GetInstance()->GetTexture(ORIBOMD));
}
