#pragma once
#include "object3D.h"


//�_�������Ă�G�̓��̏�Ƀ|���S���񂵂���J������G�̕����ɌŒ肵���肷��N���X

class Enemy;

class TargetSelect : public object3D
{
private:
	Enemy* _enemy;
	std::vector<Enemy*>_enemys;
	int _select;
	int _enemyMax;
	int _oldSelectMode;	//�ǂ̍s������J�ڂ��Ă�����

public:
	TargetSelect();
	~TargetSelect();

	void Init();
	void Uninit();
	void Update();
	void Draw();
	void Set(int oldSelect);

	void ChangePhase();		//����Ȑ݌v���������Ɩ{���ɐ\����Ȃ��Ƃ������Ă���
};

