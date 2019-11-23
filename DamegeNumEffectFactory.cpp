#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "GameObject.h"
#include "DamegeNumEffect.h"
#include "DamegeNumEffectFactory.h"
#include "scene.h"

DamegeNumEffectFactory* DamegeNumEffectFactory::_instance = nullptr;


void DamegeNumEffectFactory::CreateInstance()
{

}

void DamegeNumEffectFactory::Delete()
{
	if (_instance != nullptr) {
		delete _instance;
		_instance = nullptr;
	}
}

DamegeNumEffectFactory* DamegeNumEffectFactory::GetInstance()
{
	if (_instance != nullptr) {
		return _instance;
	}

	return nullptr;
}

void DamegeNumEffectFactory::CreateEffect(XMFLOAT3 position, int numDamege)
{
	Scene* scene = CManager::GetScene();

	int CountStopValue = 1; //�J���X�g��

	int digit = log10(numDamege) + 1; //����

	int damege = numDamege;

	for (int i = 0; i < digit; ++i) {
		CountStopValue *= 10;
	}

	//�J���X�g���Ă邩�ǂ���
	if (numDamege >= CountStopValue) {
		damege = CountStopValue - 1;
	}


	for (int i = digit - 1; i >= 0; --i) {

		DamegeNumEffect* effect = scene->AddGameObject<DamegeNumEffect>(TYPE_EFFECT);
		effect->Set(position, numDamege);
	}

}


