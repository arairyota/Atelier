#ifndef MANAGER_H
#define MANAGER_H


class Scene; //前方宣言 ポインタの時でしか使えない

class CManager
{
private:
	static Scene* _Scene;

public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	static Scene* GetScene();

	template <typename T>
	static void SetScene() {
		if (_Scene != nullptr) {
			_Scene->Uninit();
			delete _Scene;
		}

		_Scene = new T();
		_Scene->Init();
	};
}; 

#endif // !MANAGER_H