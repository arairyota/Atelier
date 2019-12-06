#ifndef BATTLEJUDG_H
#define BATTLEJUDG_H

class BattleJudg
{
	static unsigned int _numDamege;

public:
	BattleJudg();
	~BattleJudg();

	static unsigned int DamageJudg(float attack, float def, XMFLOAT3 position);
	static bool IsDeath(int hp);
	static bool IsClear(int size);

	void Init() ;
	void Uninit() {};
	void Update() {};
	void Draw() {};
};

#endif // BATTLEJUDG_H