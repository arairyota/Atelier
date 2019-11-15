#pragma once
#include "object3D.h"


//狙いをつけてる敵の頭の上にポリゴン回したりカメラを敵の方向に固定したりするクラス

class Enemy;

class TargetSelect : public object3D
{
private:
	Enemy* _enemy;
	std::vector<Enemy*>_enemys;
	int _select;
	int _enemyMax;
	int _oldSelectMode;	//どの行動から遷移してきたか

public:
	TargetSelect();
	~TargetSelect();

	void Init();
	void Uninit();
	void Update();
	void Draw();
	void Set(int oldSelect);

	void ChangePhase();		//こんな設計をしたこと本当に申し訳ないとおもっている
};

