#ifndef ENEMY_H
#define ENEMY_H

#define ENEMY_ATTACK_WAIT_TIME	(100)

#define ENEMY_INIT_FLAG			(0x00)
#define ENEMY_ATTACK_FLAG		(0x01)

#include "gameActor.h"
#include "player.h"
class CModel;
class Player;

class Enemy : public GameActor {
private:
	XMFLOAT3  _len;
	unsigned char _actFlag;		//Ç«ÇÃçsìÆÇÇµÇƒÇ¢ÇÈÇ©

	ModelAnimation* _testModel;

public:
	Enemy() { _actFlag = ENEMY_INIT_FLAG; };

	void Init();
	void Uninit();
	void Update();
	void Draw();
	void Set(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scale, CHARACTER_STATS stats);
	void SetHit(bool isHit) override{ _stats._isHit = isHit; };
	void Attack() override;
	void FirstAction()override;
	void Action()override;
	void InitAnimData()override;
	XMFLOAT3 GetCameraPosition()override;
	Enemy* GetEnemy() { return this; };
	float GetLife() { return _stats._life; }
	GameActor* GetGameActor() { return this; }
	void SetActionCamera() {};
};

#endif // !ENEMY_H
