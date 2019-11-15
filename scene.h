#ifndef SCENE_H
#define SCENE_H

#include <list>
#include <typeinfo>
#include <vector>
#include "renderer.h"
#include "GameObject.h"
#include "camera.h"
#include "Mesh.h"
#include "MeshCylinder.h"
#include "MeshField.h"
#include "MeshWall.h"
#include "model.h"
#include "polygon.h"
#include "player.h"
#include "enemy.h"
#include "billboard.h"
#include "ModelLoader.h"
#include "Town.h"
#include "playerInterface.h"
#include "TargetSelect.h"
#include "BattleJudg.h"
#include "ActionPhase.h"

static enum list_type {
	TYPE_zero = 0,
	TYPE_CAMERA,
	TYPE_FIELD,
	TYPE_PLAYER,
	TYPE_ENEMY,
	TYPE_OBJECT,
	TYPE_EFFECT,
	TYPE_WIDGET,
	TYPE_JUDG,
	TYPE_LIST_MAX,
} list_typeObject;

class Scene{
protected:
	std::list<GameObject*> _GameObject[TYPE_LIST_MAX];

public:
	Scene() {}
	virtual ~Scene() {}
	virtual void Init() = 0;

	virtual void Uninit() {
		for (int cnt = 0; cnt < TYPE_LIST_MAX; cnt++) {
			for (GameObject* object : _GameObject[cnt]) {
				object->Uninit();
				delete object;
			}
			_GameObject[cnt].clear();
		}
	}

	virtual void Update() {
		for (int cnt = 0; cnt < TYPE_LIST_MAX; cnt++) {
			for (GameObject* object : _GameObject[cnt]) {
				object->Update();
			}
			_GameObject[cnt]._Remove_if([](GameObject* object) { 
				return object->Destroy(); }); //[]ñºëOÇÃÇ»Ç¢ä÷êî(ÇÃà¯êî){ÇÃèàóù}
		}
	}

	virtual void Draw() {
		for (int cnt = 0; cnt < TYPE_LIST_MAX; cnt++) {
			for (GameObject* object : _GameObject[cnt]) {
				object->Draw();
			}
		}
	}

	template<typename T>
	auto* AddGameObject(int Layer) {
		T* object = new T();
		_GameObject[Layer].push_back(object);
		object->Init();
		return object;
	}

	//
	template <typename T>
	T* GetGameObject(int layer) {
		for (GameObject* object : _GameObject[layer]) {
			if (typeid(*object) == typeid(T)) {
				return (T*)object;
			}
		}
		return nullptr;
	}

	void DestroyGameObject(GameObject* object) {
		object->SetDestroy();
	}

	//ï°êîìñÇΩÇËîªíË
	template <typename T>
	std::vector<T*> GetGameObjects(int layer) {
		std::vector<T*> objects;
		for (GameObject* object : _GameObject[layer]) {
			if (typeid(*object) == typeid(T)) {
				objects.push_back((T*)object);
			}
		}
		return objects;
	}

};

#endif // !SCENE_H
