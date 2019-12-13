#ifndef PLAYERINTERFACE_H
#define PLAYERINTERFACE_H
#include "object2D.h"
class attackUi;
class itemUi;
class skillUi;

class playerInterface : public Object2D
{
private:
	//‚È‚ñ‚©actionUi“I‚È‚Ì‚½‚¹‚é
	bool _isActionPhase; //‚Ç‚ê‚ğ‘€ì‚Å‚«‚é‚©ŠÇ—‚·‚éƒtƒ‰ƒO
	attackUi* _attackUi;
	itemUi* _itemUi;
	skillUi* _skillUi;

	const float _move = 200.0f;
	float _uiPos;

	unsigned char _selectType;

public:
	playerInterface() { _selectType = 0x00; };
	~playerInterface() {};

	void Init()override;
	void Uninit()override;
	void Update()override;
	void Set();
};

#endif // !PLAYERINTERFACE_H