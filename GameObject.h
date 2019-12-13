#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <d3d11.h>
//#include <DirectXMath.h>

#define ROTASION_SPEED (5.0f)

class CTexture;

class GameObject {
private:
	bool _isDestroy = false;
	
public:
	GameObject() { _isFirst = true; };
	virtual ~GameObject() {};
	virtual void Init() {};
	virtual void Uninit() {};
	virtual void Update() {};
	virtual void Draw() {};

	void SetDestroy() { _isDestroy = true; };
	bool GetDestroy() { return _isDestroy; }
	bool Destroy() {
		if (_isDestroy) {
			this->Uninit();
			delete this;
			return true;
		}
		else {
			return false;
		}
	}

protected:
	bool _isFirst = true;	//一度だけ行う処理に使うフラグ
	const XMFLOAT3 _INITPOSITON = XMFLOAT3(0.0f, 20.0f, 70.0f);
	const XMFLOAT3 _PLAYERPOSITION = XMFLOAT3(10.0f, 30.0f, -60.0f);
	const XMFLOAT3 _ENEMYPOSITION = XMFLOAT3(0.0f, 0.0f, 0.0f);
	CTexture* _Texture = NULL;			//テクスチャ
};

#endif // !GAMEOBJECT_H

