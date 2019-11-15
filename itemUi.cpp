#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "GameScene.h"
#include "SortTurn.h"
#include "ItemBase.h"
#include "ItemManager.h"
#include "ItemPoach.h"
#include "skillUi.h"
#include "actionUi.h"
#include "itemUi.h"
#include "input.h"
#include "Flag.h"
#include "OriBomd.h"
#include "scene.h"


itemUi::itemUi()
{
	actionUi::actionUi();
}


itemUi::~itemUi()
{
}

void itemUi::Init()
{
	actionUi::Init();
}

void itemUi::Uninit()
{
	actionUi::Uninit();
}

void itemUi::Update()
{
	actionUi::Update();

	if (Flag::GetGamePhase() == FLAG_ITEM_SELECT) {
		if (_isFirst) {
			Scene* scene = CManager::GetScene();
			ItemPoach* itemPoach = scene->AddGameObject<ItemPoach>(TYPE_WIDGET);
			//itemPoach->Init();
			_isFirst = false;
		}
	}
	else _isFirst = true;
}

void itemUi::Draw()
{
	if (Flag::GetGamePhase() == FLAG_ACTION_SELECT) {
		actionUi::Draw();
	}

	if (Flag::GetGamePhase() == FLAG_ITEM_SELECT) {

	}
}

void itemUi::Set(XMFLOAT2 position, XMFLOAT2 rotation, XMFLOAT2 scale, XMMATRIX mtx, CTexture* texture)
{
	actionUi::Set(position, rotation, scale, mtx, texture);
}
