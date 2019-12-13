#ifndef SCENE_H
#define SCENE_H

#include <typeinfo>
#include <list>
#include <vector>

#include "GameObject.h"

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

	virtual void Uninit();

	virtual void Update();

	virtual void Draw();

	template<typename T>
	auto* AddGameObject(int Layer);

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
	std::vector<T*> GetGameObjects(int layer);

};

template<typename T>
inline auto* Scene::AddGameObject(int Layer)
{
	T* object = new T();
		_GameObject[Layer].push_back(object);
		object->Init();
		return object;
}

template<typename T>
inline std::vector<T*> Scene::GetGameObjects(int layer)
{
	std::vector<T*> objects;
	for (GameObject* object : _GameObject[layer]) {
		if (typeid(*object) == typeid(T)) {
			objects.push_back((T*)object);
		}
	}
	return objects;
}
#endif // !SCENE_H