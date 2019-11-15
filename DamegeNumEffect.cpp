#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "TextureManager.h"
#include "billboard.h"
#include "Timer.h"
#include "GameObject.h"
#include "DamegeNumEffect.h"

void DamegeNumEffect::Init()
{
	Billboard::Init();

	_beginFrame = Timer::GetNowTime();


}

void DamegeNumEffect::Uninit()
{
	Billboard::Uninit();
}

void DamegeNumEffect::Update()
{
	Billboard::Update();
}

void DamegeNumEffect::Draw()
{
	Billboard::Draw();
}

void DamegeNumEffect::Set(XMFLOAT3 position, int damegeNum)
{
	////カンスト数値を求める
	//int CountStopValue = 1;

	//for (int i = 0; i < 5; i++)
	//{
	//	CountStopValue *= 10;
	//}

	////カンストしてるかどうか
	//if (damegeNum >= CountStopValue)
	//{
	//	damegeNum = CountStopValue - 1;
	//}

	//for (int i = 5 - 1; i >= 0; i--)
	//{
	//	Billboard::Set(position, XMFLOAT3(5.0f, 5.0f, 5.0f), NUMBER, damegeNum);
	//	damegeNum /= 10;
	//}
	Billboard::Set(position, XMFLOAT3(5.0f, 5.0f, 5.0f), TextureManager::GetInstance()->GetTexture(NUMBER));
}

