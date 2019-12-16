#ifndef GAMEACTOR_H
#define GAMEACTOR_H

#include "object3D.h"

struct CHARACTER_STATS {
	float _life;	//�̗�
	float _mp;		//�}�W�b�N�|�C���g
	float _bp;		//�u���C�N�|�C���g

	float _atk;		//�U����
	float _def;		//�h���
	float _spd;		//���΂₳

	bool _isHit;	//�^�[�Q�b�g�ɂ��ꂽ���ǂ���
	bool _nowTurn;	//�����̃^�[�����ǂ���

	float _waitTime; //�҂���

	CHARACTER_STATS() = default;

	CHARACTER_STATS(const CHARACTER_STATS&) = default;
	CHARACTER_STATS& operator=(const CHARACTER_STATS&) = default;

	CHARACTER_STATS(CHARACTER_STATS&&) = default;
	CHARACTER_STATS& operator=(CHARACTER_STATS&&) = default;

	CHARACTER_STATS(float life, float mp, float bp, float atk, float def, float spd) : _life(life), _mp(mp), _bp(bp), _atk(atk), _def(def), _spd(spd) {};

};

struct AttackAnimationData{
	
	unsigned int startFlame;
	unsigned int nowFlame;
	bool is_Finish;
	XMFLOAT3 cameraPosition;
};

class CModel;

class GameActor : public object3D{
private:
	
public:
	CHARACTER_STATS _stats;
	AttackAnimationData _atkAnimData;

	virtual void Attack() = 0;
	virtual void FirstAction() = 0;				//Turn�������Ă��Ĉ�ԍŏ��ɂ���s��
	virtual void Action() = 0;					//
	virtual void SetHit(bool isHit) =0;
	virtual void InitAnimData()=0;

	virtual XMFLOAT3 GetCameraPosition()=0;
	virtual float GetLife()=0;
	virtual GameActor* GetGameActor() { return this; }
	virtual void SetWaitTime(int waitTime) { _stats._waitTime += waitTime; }

protected:
	XMFLOAT3 _cameraPosition;
};

#endif // !GAMEOBJECT_H
