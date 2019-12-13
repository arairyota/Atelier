#ifndef BULLET_H
#define BULLET_H

#include "gameActor.h"
class CModel;

#define BULLET_SPEED (2)

class Bullet : public GameActor {
private:
	CModel* _model;
	int _life;

public:
	Bullet() {};
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void Creat(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scale, XMVECTOR front, XMVECTOR right, XMVECTOR up, int life);
	void Destroy();
};

#endif // !BULLET_H
