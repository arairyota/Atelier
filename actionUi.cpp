#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "polygon.h"
#include "actionUi.h"

void actionUi::Init()
{
	CPolygon::Init();

	_is_select = false;
	
}

void actionUi::Uninit()
{
	CPolygon::Uninit();
}

void actionUi::Update()
{
	//CRenderer::SetLight();
	CPolygon::Update();
}

void actionUi::Draw()
{
	CPolygon::Draw();
}

void actionUi::Set(XMFLOAT2 position, XMFLOAT2 rotation, XMFLOAT2 scale, XMMATRIX mtx, CTexture* texture)
{
	CPolygon::Set(position, rotation, scale, mtx, texture);
}
