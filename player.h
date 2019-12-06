#ifndef PLAYER_H
#define PLAYER_H

#include "gameActor.h"
class CPolygon;
class Enemy;
class ModelAnimation;
class CharacterUI;

#define PLAYER_SPEED (1)

class Player : public GameActor {
private:
	XMFLOAT3 _len;
	ModelAnimation* _testModel;
	CharacterUI* _charaUI;

	int _animFrame = 0;

public:
	Player() {};
	void Init(); //�K���ɏ��������邽�߂���
	void Uninit();
	void Update();
	void Draw();
	void Set(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scale, CHARACTER_STATS stats); //�F�X�Z�b�g����
	void InitAnimData() override;
	void SetHit(bool isHit) override { _stats._isHit = isHit; };
	void FirstAction()override;
	void Attack() override;
	void Action() override;
	Player* GetPlayer() { return this; };
	XMFLOAT3 GetCameraPosition()override;
	float GetLife() { return _stats._life; }
	GameActor* GetGameActor() { return this; }

	
};

#endif // !PLAYER_H
