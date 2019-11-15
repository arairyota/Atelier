#include "main.h"
#include "BattleJudg.h"

unsigned int BattleJudg::_numDamege = 0;

BattleJudg::BattleJudg()
{

}


BattleJudg::~BattleJudg()
{
}

unsigned int BattleJudg::DamageJudg(float attack, float def)
{
	_numDamege = 0;

	if ((attack - def) < 0) return 0;

	_numDamege = attack - def;

	return _numDamege;
}
