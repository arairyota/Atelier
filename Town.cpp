#include "main.h"
#include "renderer.h"
#include "model.h"
#include "ModelLoader.h"
#include "ModelMesh.h"
#include "WICTextureLoader.h"
#include "Town.h"
#include "scene.h"



Town::Town()
{
}


Town::~Town()
{
}

void Town::Init()
{
	_position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	_rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	_scale = XMFLOAT3(0.0f, 0.0f, 0.0f);

	_modelA = nullptr;
	_modelB = nullptr;
}

void Town::Uninit()
{
	_modelA->Close();
}

void Town::Update()
{
}

void Town::Draw()
{
	// マトリクス設定
	XMMATRIX world;
	world = XMMatrixScaling(_scale.x, _scale.y, _scale.z);
	world *= XMMatrixRotationRollPitchYaw(_rotation.x, _rotation.y, _rotation.z);
	world *= XMMatrixTranslation(_position.x, _position.y, _position.z);
	CRenderer::SetWorldMatrix(&world);

	_modelA->Draw(CRenderer::GetDeviceContext());
}

void Town::Set(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scale)
{
	_position = pos;
	_rotation = rot;
	_scale = scale;

	_modelA = new ModelLoader;

	//_modelA->Load(GetWindow(), CRenderer::GetDevice(), CRenderer::GetDeviceContext(), "asset/tank.obj");
	_modelA->Load(GetWindow(), CRenderer::GetDevice(), CRenderer::GetDeviceContext(), "asset/TownModel/kadai/skydome.obj");
}
