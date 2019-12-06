#include <list>
#include <vector>
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "SortTurn.h"
#include "Flag.h"
#include "input.h"
#include "object2D.h"
#include "polygon.h"
#include "texture.h"
#include "TextureManager.h"
#include "ItemBase.h"
#include "ItemManager.h"
#include "TargetSelect.h"
#include "ItemPoach.h"
#include "scene.h"

void ItemPoach::Init()
{
	Scene* scene = CManager::GetScene();

	CPolygon::Init();

	_position = XMFLOAT2(320,540);
	_rotation = XMFLOAT2(0.0f, 0.0f);
	_scale = XMFLOAT2(1.0f, 1.0f);
	_Texture = TextureManager::GetInstance()->GetTexture(ITEMPOACH);
	_select = 0;

	XMMATRIX world = XMMatrixIdentity();
	CPolygon::Set(_position, _rotation, _scale, XMMatrixIdentity(), _Texture);
	world *= XMMatrixScaling(_scale.x, _scale.y, 1.0f);
	world *= XMMatrixTranslation(_position.x, _position.y, 0.0f);

	//_texture = TextureManager::GetInstance()->GetTexture(ITEMPOACH);
	UINT cntX = 1;
	UINT cntY = 1;

	/*for (short cnt = 0; cnt < ITEMPOACH_MAX; ++cnt) {
		_ItemPoachList.back()->SetPosition2D(PoachPosition[cnt].x, PoachPosition[cnt].y);
	}*/
	short cnt = 0;
	for (auto& item : ItemManager::GetInstance()->GetItemList()) {
		_ItemPoachList.push_back(item);
		item->SetPolygon(scene->AddGameObject<CPolygon>(TYPE_WIDGET));
		item->GetPolygon()->Set(XMFLOAT2(0.0f, 0.0f), INIT_XMFLOAT2, XMFLOAT2(1.0f, 1.0f), world, item->GetTexture());
		cnt++;
	}
	cnt = 0;

	_cursor = scene->AddGameObject<CPolygon>(TYPE_WIDGET);

	_cursor->Set(XMFLOAT2(0.0f, 0.0f), INIT_ROTATION2D, XMFLOAT2(1.0f, 1.0f), world, TextureManager::GetInstance()->GetTexture(CURSOR));
}

void ItemPoach::Uninit()
{
	for (auto& item : ItemManager::GetInstance()->GetItemList()) {
		item->GetPolygon()->SetDestroy();
	}
	_cursor->SetDestroy();
	CPolygon::Uninit();
	this->SetDestroy();
}

void ItemPoach::Update()
{
	if (Flag::GetGamePhase() == FLAG_ITEM_SELECT) {
		
		if (_isFirst) {
			if (_waitFrame < 2) {
				++_waitFrame;
				return; 
			}

			CPolygon::SetDrawFlag(true);
			for (auto item : _ItemPoachList) {
				item->GetPolygon()->SetDrawFlag(true);
				_cursor->SetDrawFlag(true);
			}
			_isFirst = false;
			CPolygon::Update();
			
		}

		if (CInput::GetKeyTrigger('W')) {
			if (_select > 4) {
				_select -= 5;
			}
		}

		if (CInput::GetKeyTrigger('S')) {
			if (_select < 19) {
				_select += 5;
			}
		}

		if (CInput::GetKeyTrigger('A')) {
			if (_select > 0) {
				_select -= 1;
			}
		}

		if (CInput::GetKeyTrigger('D')) {
			if (_select < 24) {
				_select += 1;
			}
		}

		if (CInput::GetKeyTrigger('E')) {
			TargetSelect* targetSelect = CManager::GetScene()->AddGameObject<TargetSelect>(TYPE_OBJECT);
			targetSelect->Set(FLAG_ITEM_SELECT);
			_isFirst = true;
			Uninit();
		}

		if (CInput::GetKeyTrigger('Q')) {
			Flag::SetGamePhase(FLAG_ACTION_SELECT);
			_select = 0;
			Uninit();
			_isFirst = true;
			
		}
		_cursor->SetPositon(XMFLOAT2(PoachPosition[_select].x + 50.0f, PoachPosition[_select].y - 50.0f));
	}
	else {
		if (_isFirst) {
			CPolygon::SetDrawFlag(false);
			for (auto item : _ItemPoachList) {
				item->GetPolygon()->SetDrawFlag(false);
				_cursor->SetDrawFlag(false);
			}
			_isFirst = false;
		}
		//_ItemPoachList[_select]->GetPolygon()->SetDrawFlag(false);
	}
	//this->Translation(_world, _position);
}

void ItemPoach::Draw()
{
	CPolygon::Draw();
	for (auto& item : ItemManager::GetInstance()->GetItemList()) {
		//item->GetPolygon()->
	}
}

void ItemPoach::Set(XMFLOAT2 position, XMFLOAT2 rotation, XMFLOAT2 scale, XMMATRIX mtx, CTexture * texture)
{
	
	//Scene* scene = CManager::GetScene();
	
	//_polygon = scene->AddGameObject<CPolygon>(TYPE_WIDGET);

	
	////world *= XMMatrixRotationRollPitchYaw(_rotation.x, _rotation.y, _rotation.z);
	//_world *= XMMatrixRotationY(_rotation.y);

	////_polygon->Set(XMFLOAT2(0.0f, 0.0f), XMFLOAT2(0.0f, 0.0f), _scale, _world, TextureManager::GetInstance()->GetTexture(ITEMPOACH));

	//CRenderer::SetWorldViewProjection2D(_position, _rotation, _scale, _world);
	//_polygon->Set(_position, XMFLOAT2(2.0f, 2.0f), XMFLOAT2(2.0f, 2.0f), _world, TextureManager::GetInstance()->GetTexture(ITEMPOACH));

	
}

ItemBase * ItemPoach::GetSelectItem()
{
	return _ItemPoachList[_select];
}
