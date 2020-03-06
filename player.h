#ifndef PLAYER_H
#define PLAYER_H

#include <list>
#include <vector>
#include "CameraData.h"
#include "gameActor.h"

class CPolygon;
class Enemy;
class ModelAnimation;
class CharacterUI;
class CameraData;

#define PLAYER_SPEED (1)

class Player : public GameActor {
private:
	XMFLOAT3 _len;
	ModelAnimation* _testModel;
	CharacterUI* _charaUI;

	int _animFrame = 0;

	CameraData _cameraListv[100];
	std::list<CameraData*> _cameraList;

public:
	Player() {};
	void Init(); //適当に初期化するためだけ
	void Uninit();
	void Update();
	void Draw();
	void Set(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scale, CHARACTER_STATS stats); //色々セットする
	void InitAnimData() override;
	void SetHit(bool isHit) override { _stats._isHit = isHit; };
	void FirstAction()override;
	void Attack() override;
	void Action() override;
	Player* GetPlayer() { return this; };
	XMFLOAT3 GetCameraPosition()override;
	float GetLife() { return _stats._life; }
	GameActor* GetGameActor() { return this; }
	void SetActionCamera();
	
};

#endif // !PLAYER_H
