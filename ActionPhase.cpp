#include <list>
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "Flag.h"
#include "SortTurn.h"
#include "gameActor.h"
#include "player.h"
#include "enemy.h"
//
#include "ActionPhase.h"
//#include "scene.h"

Player* ActionPhase::_player;
std::vector<Enemy*>ActionPhase::_enemys;
std::list<GameActor*>ActionPhase::_actors;
GameActor* ActionPhase::_firstTurn;

ActionPhase::ActionPhase()
{
}


ActionPhase::~ActionPhase()
{
}

void ActionPhase::Update()
{
	if (Flag::GetGamePhase() != FLAG_ACTION_PHASE) return;

	SortTurn::GetGameActorFront()->Action();
}


