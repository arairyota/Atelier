#pragma once

//2進数メモ
//1		0001
//2		0010
//3		0011
//4		0100
//5		0101
//6		0110
//7		0111
//8		1000
//9		1001
//A		1010
//B		1011
//C		1100
//D		1101
//E		1110
//F		1111

#define FLAG_INIT			(0x00)

//_GamePhaseFlag
#define FLAG_ACTION_SELECT	(0x01) //0000 0001
#define FLAG_ITEM_SELECT	(0x02) //0000 0010
#define FLAG_ATTACK_SELECT	(0x04) //0000 0100
#define FLAG_SKILL_SELECT	(0x08) //0000 1000
#define FLAG_TARGET_SELECT	(0x10) //0001 0000
#define FLAG_ACTION_PHASE	(0x11) //0001 0001

//SelectActionFlag



class Flag
{
private:
	static unsigned char _GamePhaseFlag;		//攻撃とか敵の選択とか今どのフェーズにいるか
	static unsigned char _SelectActionFlag;		//どのactionを選択したか
	static bool _TurnLoopFlag;					//ループしてるかどうか

public:
	Flag() { _GamePhaseFlag = FLAG_INIT; _SelectActionFlag = FLAG_INIT; _TurnLoopFlag = false; };
	~Flag() {};

	static void SetGamePhase(int PhaseFlag);
	static int GetGamePhase();

	static void SetSelectAction(int ActionFlag);
	static int GetSelectAction();

	static bool GetTurnLoopFlag();
	static void SetTurnLoopFlag(bool flag);

	//static void SetNextPhase(int PhaseFlag){_GamePhaseFlag ^= _GamePhaseFlag;};
	//static void Leftshift();

};

