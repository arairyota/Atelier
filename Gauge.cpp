#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "TextureManager.h"
#include "gameActor.h"
#include "Gauge.h"
#include "scene.h"

void Gauge::Init()
{

	Scene* scene = CManager::GetScene();
	_base = scene->AddGameObject<CPolygon>(TYPE_WIDGET);
	_gauge = scene->AddGameObject<CPolygon>(TYPE_WIDGET);
	
	_len = HP_BAR_LEN;
}

void Gauge::Update()
{
	_len = (*_valuePtr / _maxValue) * HP_BAR_LEN;

	_gauge->SetScaleX(_len);

}

void Gauge::Draw()
{
}

void Gauge::Uninit()
{

}

void Gauge::Set(XMMATRIX world, float* value)
{
	_valuePtr = value;
	_maxValue = *_valuePtr;
	_base->SetLeftToRight(XMFLOAT2(0.0f, 0.0f), XMFLOAT2(0.0f, 0.0f), XMFLOAT2(_len, 10.0f), world, TextureManager::GetInstance()->GetTexture(BLACKBAR));
	_gauge->SetLeftToRight(XMFLOAT2(0.0f, 0.0f), XMFLOAT2(0.0f, 0.0f), XMFLOAT2(_len, 10.0f), world, TextureManager::GetInstance()->GetTexture(REDBAR));
	
}
