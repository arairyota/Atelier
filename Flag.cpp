#include "main.h"
#include "Flag.h"

unsigned char Flag::_GamePhaseFlag = 0x00;
unsigned char Flag::_SelectActionFlag = 0x00;
bool Flag::_TurnLoopFlag = false;

void Flag::Init()
{
	_GamePhaseFlag = FLAG_INIT; 
	_SelectActionFlag = FLAG_INIT; 
	_TurnLoopFlag = false;
}

void Flag::SetGamePhase(int PhaseFlag)
{
	_GamePhaseFlag = PhaseFlag;
}

int Flag::GetGamePhase()
{
	return _GamePhaseFlag;
}

void Flag::SetSelectAction(int ActionFlag)
{
	_SelectActionFlag = ActionFlag;
}

int Flag::GetSelectAction()
{
	return _SelectActionFlag;
}

bool Flag::GetTurnLoopFlag()
{
	return _TurnLoopFlag; 
}

void Flag::SetTurnLoopFlag(bool flag)
{
	_TurnLoopFlag = flag;
}
