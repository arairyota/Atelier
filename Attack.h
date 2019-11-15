#pragma once

class Player;
class Enemy;

class Attack
{
private:
	Player* _player;
	Enemy* _enemy;

public:
	Attack();
	~Attack();

	void Init();
	void Update();
	void Set(Player* player, Enemy* enemy);
};

