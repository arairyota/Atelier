#include "main.h"
#include "renderer.h"
#include "ItemBase.h"
#include "OriBomd.h"
#include "ItemManager.h"

ItemManager* ItemManager::_instance = nullptr;

bool ItemManager::AllLoad()
{
	_itemList.push_back(AddItem<OriBomd>());
	_itemList.back()->Init();
	return true;
}

void ItemManager::AllUnLoad()
{
	for (auto it = _itemList.begin(); it != _itemList.end();) {
		ItemBase* item = *it;
		it = _itemList.erase(it);
		delete item;
	}
}

ItemBase* ItemManager::GetItem(ITEM_INDEX index)
{
	return _itemList[index];
}
