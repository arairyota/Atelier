#pragma once
#include "BattleTransition.h"

class BattleJudg : public BattleTransition
{
	static unsigned int _numDamege;

public:
	BattleJudg();
	~BattleJudg();

	static unsigned int DamageJudg(float attack, float def, XMFLOAT3 position);
	static bool IsDeath(int hp) {
		if (hp < 0) {
			return true;
		}
		else return false;
};

	void Init() {};
	void Uninit() {};
	void Update() {};
	void Draw() {};
};

