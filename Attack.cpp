#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "Attack.h"
#include "player.h"
#include "enemy.h"


Attack::Attack()
{
}


Attack::~Attack()
{
}

void Attack::Update()
{
	//_player->
}

void Attack::Set(Player * player, Enemy * enemy)
{
	_player = player;
	_enemy = enemy;

}
