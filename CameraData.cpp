#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "model.h"
#include "CameraData.h"

CameraData::CameraData()
{
	_position =  XMFLOAT3(0.0f, 20.0f, 0.0f);
	_viewFront = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	_viewRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	_viewUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	_model = new CModel;
	_model->Load("asset/TargetSelect.obj");
}

void CameraData::Init()
{

}

void CameraData::Uninit()
{
	_model->Unload();
}

void CameraData::Update()
{

}

void CameraData::Draw()
{
	_model->Draw();
}

XMFLOAT3 CameraData::GetPosition()
{
	return _position;
}
