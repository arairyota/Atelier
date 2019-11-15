/*****************************************************************************
SortTurn.h
SortTurn.h
name	:新井 崚太
data	:2019/07/18 16:55:31
*****************************************************************************/
#ifndef SortTurn_H
#define SortTurn_H

//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include <list>
#include <algorithm>
#include "Flag.h"
#include "gameActor.h"

//////////////////////////////////////////////////////////////////////////////
//define定義
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//前方宣言
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//SortTurnクラス
//////////////////////////////////////////////////////////////////////////////
class SortTurn {
private:
	static std::list<GameActor*> _GameActor;
	std::list<GameActor*>::iterator it = _GameActor.begin();
public:
	//右と左比較する(昇順)
	static bool comp(GameActor* la, GameActor* ra) {
		return la->_stats._waitTime < ra->_stats._waitTime;
	}
	
	//[](GameActor& la, GameActor& ra) { return (la._stats._spd > ra._stats._spd); }

	static void Sort() {
		if (_GameActor.front() == nullptr) return;
		_GameActor.sort(comp);
	};

	//WaitTimeの一番少ないやつ
	static void BeginTurn() {
		if (Flag::GetTurnLoopFlag()) return;
		Sort();
		_GameActor.front()->FirstAction();
		Flag::SetTurnLoopFlag(true);
	}
	
	template<typename T>
	static auto* AddGameActor() {
		T* actor = new T;
		_GameActor.push_back(actor);
		return actor;
	};

	static std::list<GameActor*> GetGameActors() {
		
		return _GameActor;
	}

	//ターン待ちの一番先頭を呼ぶ
	static GameActor* GetGameActorFront() {
		return _GameActor.front();
	}

	static void SetActor(GameActor* actor) {
		_GameActor.push_back(actor);
	}
protected:

};

#endif // !SortTurn_H

//void Init();
//void Uninit();
//void Update();
//void Draw();
