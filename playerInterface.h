#ifndef PLAYERINTERFACE_H
#define PLAYERINTERFACE_H
#include "object2D.h"
class attackUi;
class itemUi;
class skillUi;

class playerInterface : public Object2D
{
private:
	//�Ȃ�actionUi�I�Ȃ̎�������
	bool _isActionPhase; //�ǂ�𑀍�ł��邩�Ǘ�����t���O
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