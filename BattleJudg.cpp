#include "main.h"
#include "manager.h"
#include "texture.h"
#include "GameObject.h"
#include "DamegeNumEffectFactory.h"
#include "BattleJudg.h"
#include "scene.h"

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

	//計算結果が０だったら
	if ((attack - def) < 0) { 
		//ダメージエフェクト
		DamegeNumEffectFactory::GetInstance()->CreateEffect(position, _numDamege);
		//DamegeNumEffect* effect = scene->AddGameObject<DamegeNumEffect>(TYPE_EFFECT);
		//effect->Set(position, _numDamege);
		return 0; 
	}

	_numDamege = attack - def;

	//ダメージエフェクト
	DamegeNumEffectFactory::GetInstance()->CreateEffect(position, _numDamege);

	return _numDamege;
}
