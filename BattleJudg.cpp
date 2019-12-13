#include "main.h"
#include "manager.h"
//#include "texture.h"
#include "GameObject.h"
#include "DamegeNumEffectFactory.h"
#include "scene.h"
#include "ResultScene.h"
#include "BattleJudg.h"

unsigned int BattleJudg::_numDamege = 0;

BattleJudg::BattleJudg()
{

}


BattleJudg::~BattleJudg()
{

}

unsigned int BattleJudg::DamageJudg(float attack, float def, XMFLOAT3 position)
{
	Scene* scene = CManager::GetScene();
	_numDamege = 0;

	//�v�Z���ʂ��O��������
	if ((attack - def) < 0) { 
		//�_���[�W�G�t�F�N�g
		DamegeNumEffectFactory::GetInstance()->CreateEffect(position, _numDamege);
		//DamegeNumEffect* effect = scene->AddGameObject<DamegeNumEffect>(TYPE_EFFECT);
		//effect->Set(position, _numDamege);
		return 0; 
	}

	_numDamege = attack - def;

	//�_���[�W�G�t�F�N�g
	DamegeNumEffectFactory::GetInstance()->CreateEffect(position, _numDamege);

	return _numDamege;
}

bool BattleJudg::IsDeath(int hp)
{
	if (hp < 0) {
		return true;
	}
	else return false;
}

bool BattleJudg::IsClear(int size)
{
	if (size == 0) {
		//�^�C�g���ɖ߂�
		CManager::SetScene<ResultScene>();
		int a = 0;
		return true;
	}
	return false;
}

void BattleJudg::Init()
{
}
