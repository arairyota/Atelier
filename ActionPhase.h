#pragma once
#include <list>
class Player;
class Enemy;
class GameActor;

class ActionPhase
{
private:
	static Player* _player;
	static std::vector<Enemy*>_enemys;
	static std::list<GameActor*>_actors;
	static GameActor* _firstTurn;

public:
	ActionPhase();
	~ActionPhase();

	static void Init() {};
	static void Uninit() {};
	static void Update();
	static void Draw() {};

};

