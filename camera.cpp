#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "GameObject.h"
#include "camera.h"
#include "Flag.h"
#include "scene.h"

void CCamera::Init()
{
	Scene* scene = CManager::GetScene();
	

	_position = XMFLOAT3(_INITPOSITON);
	_rotation = XMFLOAT3(-0.5f, 3.14, 0.0f);
	_rotation.x = 0.2f;
	_len = 5.0f;
	_atAngle = 0.0f;
	m_Viewport.left = 0;
	m_Viewport.top = 0;
	m_Viewport.right = SCREEN_WIDTH;
	m_Viewport.bottom = SCREEN_HEIGHT;
	is_Enable = true;
}


void CCamera::Uninit()
{


}


void CCamera::Update()
{
	if (CInput::GetKeyPress(VK_UP))  {
		_position.z += 1.0f;
	}

	if (CInput::GetKeyPress(VK_DOWN)) {
		_position.z += -1.0f;
	}

	if (CInput::GetKeyPress(VK_LEFT)) {
		_position.x += -1.0f;
	}

	if(CInput::GetKeyPress(VK_RIGHT)) {
		_position.x += 1.0f;
	}

	if (CInput::GetKeyPress('O')) {

	}

	if (CInput::GetKeyPress('L')) {

	}

	if (CInput::GetKeyPress('+')) {

	}

	if (CInput::GetKeyPress('K')) {

	}



	/*if (CInput::GetKeyPress('Q')) {
		_rotation.y += 0.01f;
	}*/

	/*if (CInput::GetKeyPress('E')) {
		_rotation.y -= 0.01f;
	}*/

	
	//選択したモードやスキルなどのカメラワークによって何か変える
	if (Flag::GetGamePhase() == FLAG_ACTION_SELECT) {
		_atAngle -= 0.001f;
	}

	/*if (Flag::GetGamePhase() == FLAG_TARGET_SELECT) {
 		this->Set(XMFLOAT3(50.0f, 50.0f, -50.0f), false, );
	}*/

}



void CCamera::Draw()
{
	XMMATRIX	m_InvViewMatrix;
	XMMATRIX	m_ProjectionMatrix;

	// ビューポート設定
	D3D11_VIEWPORT dxViewport;
	dxViewport.Width = (float)(m_Viewport.right - m_Viewport.left);
	dxViewport.Height = (float)(m_Viewport.bottom - m_Viewport.top);
	dxViewport.MinDepth = 0.0f;
	dxViewport.MaxDepth = 1.0f;
	dxViewport.TopLeftX = (float)m_Viewport.left;
	dxViewport.TopLeftY = (float)m_Viewport.top;

	CRenderer::GetDeviceContext()->RSSetViewports(1, &dxViewport);

	// ビューマトリクス設定
	m_InvViewMatrix = XMMatrixRotationRollPitchYaw(_rotation.x, _rotation.y, _rotation.z);
	m_InvViewMatrix *= XMMatrixTranslation(_position.x, _position.y, _position.z);
	m_InvViewMatrix *= XMMatrixRotationY(_atAngle);

	XMVECTOR det;
	m_ViewMatrix = XMMatrixInverse(&det, m_InvViewMatrix);

	CRenderer::SetViewMatrix(&m_ViewMatrix);



	// プロジェクションマトリクス設定
	m_ProjectionMatrix = XMMatrixPerspectiveFovLH(1.0f, dxViewport.Width / dxViewport.Height, 1.0f, 1500.0f);

	CRenderer::SetProjectionMatrix(&m_ProjectionMatrix);
}

void CCamera::Set(XMFLOAT3 thisPos, XMFLOAT3 thatPos)
{
	float radY = atan2f(thatPos.x - thisPos.x, thatPos.z - thisPos.z);	//Y軸回転
	float radX = -atan2f(thatPos.y - thisPos.y, thatPos.z - thisPos.z);	//X軸回転

	//radY = XMConvertToRadians(radY);
	//radX = XMConvertToRadians(radX);
	_atAngle = 0.0f;
	_position = thisPos;
	_rotation.y = radY;
	_rotation.x = 0.2;
}

