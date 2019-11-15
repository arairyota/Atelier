#include <vector>
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "object3D.h"
#include "gameActor.h"
#include "ItemBase.h"
#include "ItemManager.h"
#include "Flag.h"
#include "enemy.h"
#include "player.h"
#include "BattleJudg.h"
#include "SortTurn.h"
#include "ActionPhase.h"
#include "scene.h"

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


