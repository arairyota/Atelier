/*****************************************************************************
SortTurn.h
SortTurn.h
name	:�V�� �Ñ�
data	:2019/07/18 16:55:31
*****************************************************************************/
#ifndef SortTurn_H
#define SortTurn_H

//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include <list>
#include <algorithm>
#include "Flag.h"
#include "gameActor.h"

//////////////////////////////////////////////////////////////////////////////
//define��`
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//�O���錾
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//SortTurn�N���X
//////////////////////////////////////////////////////////////////////////////
class SortTurn {
private:
	static std::list<GameActor*> _GameActor;
	std::list<GameActor*>::iterator it = _GameActor.begin();
public:
	//�E�ƍ���r����(����)
	static bool comp(GameActor* la, GameActor* ra) {
		return la->_stats._waitTime < ra->_stats._waitTime;
	}
	
	//[](GameActor& la, GameActor& ra) { return (la._stats._spd > ra._stats._spd); }

	static void Sort() {
		if (_GameActor.front() == nullptr) return;
		_GameActor.sort(comp);
	};

	//WaitTime�̈�ԏ��Ȃ����
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

	//�^�[���҂��̈�Ԑ擪���Ă�
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
