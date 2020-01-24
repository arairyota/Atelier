#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "GameObject.h"
#include "enemy.h"
#include "camera.h"
#include "Flag.h"
#include "scene.h"



void CCamera::Init()
{
	Scene* scene = CManager::GetScene();
	
	_transQuaternion = XMQuaternionIdentity();
	_viewQuaternion = XMQuaternionIdentity();

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
	XMFLOAT3 lookPos = XMFLOAT3(0.0f, 0.0f, 10.0f);
	SetLookQuaternion(&_viewQuaternion, &lookPos);
	SetLookQuaternion(&_transQuaternion, &lookPos);
}


void CCamera::Uninit()
{


}


void CCamera::Update()
{
	//if (CInput::GetKeyPress(VK_UP))  {
	//	_position.z += 1.0f;
	//}
	//
	//if (CInput::GetKeyPress(VK_DOWN)) {
	//	_position.z += -1.0f;
	//}
	//
	//if (CInput::GetKeyPress(VK_LEFT)) {
	//	_position.x += -1.0f;
	//}
	//
	//if(CInput::GetKeyPress(VK_RIGHT)) {
	//	_position.x += 1.0f;
	//}
	//
	if (CInput::GetKeyPress(VK_SHIFT)) {
		_position.x += XMVectorGetX(_transFront) * CAMERA_SPEED;
		_position.y += XMVectorGetY(_transFront) * CAMERA_SPEED;
		_position.z += XMVectorGetZ(_transFront) * CAMERA_SPEED;
	}

	if (CInput::GetKeyPress(VK_CONTROL)) {
		_position.x += XMVectorGetX(_transFront) * -CAMERA_SPEED;
		_position.y += XMVectorGetY(_transFront) * -CAMERA_SPEED;
		_position.z += XMVectorGetZ(_transFront) * -CAMERA_SPEED;
	}

	//操縦かん的なお遊び処理
	
	{
		if (CInput::GetKeyPress('I')) {
			XMVECTOR rotation = XMQuaternionRotationAxis(_transRight, 0.05f);
			_transQuaternion = XMQuaternionMultiply(_transQuaternion, rotation);
			_transQuaternion = XMQuaternionNormalize(_transQuaternion);

			_mtxRotation = XMMatrixRotationQuaternion(_transQuaternion);

			_transUp = XMVector3TransformNormal(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), _mtxRotation);
			_transFront = XMVector3TransformNormal(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), _mtxRotation);
		}

		if (CInput::GetKeyPress('K')) {
			XMVECTOR rotation = XMQuaternionRotationAxis(_transRight, -0.05f);
			_transQuaternion = XMQuaternionMultiply(_transQuaternion, rotation);
			_transQuaternion = XMQuaternionNormalize(_transQuaternion);

			_mtxRotation = XMMatrixRotationQuaternion(_transQuaternion);

			_transUp = XMVector3TransformNormal(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), _mtxRotation);
			_transFront = XMVector3TransformNormal(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), _mtxRotation);
		}

		if (CInput::GetKeyPress('U')) {
			XMVECTOR rotation = XMQuaternionRotationAxis(_transUp, -0.05f);
			_transQuaternion = XMQuaternionMultiply(_transQuaternion, rotation);
			_transQuaternion = XMQuaternionNormalize(_transQuaternion);

			_mtxRotation = XMMatrixRotationQuaternion(_transQuaternion);

			_transFront = XMVector3TransformNormal(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), _mtxRotation);
			_transRight = XMVector3TransformNormal(XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), _mtxRotation);
		}

		if (CInput::GetKeyPress('O')) {
			XMVECTOR rotation = XMQuaternionRotationAxis(_transUp, 0.05f);
			_transQuaternion = XMQuaternionMultiply(_transQuaternion, rotation);
			_transQuaternion = XMQuaternionNormalize(_transQuaternion);

			_mtxRotation = XMMatrixRotationQuaternion(_transQuaternion);

			_transFront = XMVector3TransformNormal(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), _mtxRotation);
			_transRight = XMVector3TransformNormal(XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), _mtxRotation);
		}

		if (CInput::GetKeyPress('J')) {
			XMVECTOR rotation = XMQuaternionRotationAxis(_transFront, 0.05f);
			_transQuaternion = XMQuaternionMultiply(_transQuaternion, rotation);
			_transQuaternion = XMQuaternionNormalize(_transQuaternion);

			_mtxRotation = XMMatrixRotationQuaternion(_transQuaternion);

			_transUp = XMVector3TransformNormal(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), _mtxRotation);
			_transRight = XMVector3TransformNormal(XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), _mtxRotation);
		}

		if (CInput::GetKeyPress('L')) {
			XMVECTOR rotation = XMQuaternionRotationAxis(_transFront, -0.05f);
			_transQuaternion = XMQuaternionMultiply(_transQuaternion, rotation);
			_transQuaternion = XMQuaternionNormalize(_transQuaternion);

			_mtxRotation = XMMatrixRotationQuaternion(_transQuaternion);

			_transUp = XMVector3TransformNormal(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), _mtxRotation);
			_transRight = XMVector3TransformNormal(XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), _mtxRotation);
		}

		if (CInput::GetKeyPress(VK_UP)) {
			_position.x += XMVectorGetX(_transUp) * CAMERA_SPEED;
			_position.y += XMVectorGetY(_transUp) * CAMERA_SPEED;
			_position.z += XMVectorGetZ(_transUp) * CAMERA_SPEED;
		}

		if (CInput::GetKeyPress(VK_DOWN)) {
			_position.x -= XMVectorGetX(_transUp) * CAMERA_SPEED;
			_position.y -= XMVectorGetY(_transUp) * CAMERA_SPEED;
			_position.z -= XMVectorGetZ(_transUp) * CAMERA_SPEED;
		}

		if (CInput::GetKeyPress(VK_LEFT)) {
			_position.x -= XMVectorGetX(_transRight) * CAMERA_SPEED;
			_position.y -= XMVectorGetY(_transRight) * CAMERA_SPEED;
			_position.z -= XMVectorGetZ(_transRight) * CAMERA_SPEED;
		}

		if (CInput::GetKeyPress(VK_RIGHT)) {
			_position.x += XMVectorGetX(_transRight) * CAMERA_SPEED;
			_position.y += XMVectorGetY(_transRight) * CAMERA_SPEED;
			_position.z += XMVectorGetZ(_transRight) * CAMERA_SPEED;
		}

	}
	
	//デバック処理
	//{
	//	
	//	if (CInput::GetKeyPress('I')) {
	//		XMVECTOR rotation = XMQuaternionRotationAxis(_transRight, -0.1f);
	//		_transQuaternion = XMQuaternionMultiply(_transQuaternion, rotation);
	//		_transQuaternion = XMQuaternionNormalize(_transQuaternion);
	//
	//		//_mtxRotation = XMMatrixRotationQuaternion(_transQuaternion);
	//
	//		//_transUp = XMVector3TransformNormal(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), _mtxRotation);
	//		//_transFront = XMVector3TransformNormal(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), _mtxRotation);
	//	}
	//
	//	if (CInput::GetKeyPress('K')) {
	//		XMVECTOR rotation = XMQuaternionRotationAxis(_transRight, 0.1f);
	//		_transQuaternion = XMQuaternionMultiply(_transQuaternion, rotation);
	//		_transQuaternion = XMQuaternionNormalize(_transQuaternion);
	//
	//		//_mtxRotation = XMMatrixRotationQuaternion(_transQuaternion);
	//
	//		//_transUp = XMVector3TransformNormal(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), _mtxRotation);
	//		//_transFront = XMVector3TransformNormal(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), _mtxRotation);
	//	}
	//
	//	if (CInput::GetKeyPress('L')) {
	//		XMVECTOR rotation = XMQuaternionRotationAxis(_transUp, 0.1f);
	//		_transQuaternion = XMQuaternionMultiply(_transQuaternion, rotation);
	//		_transQuaternion = XMQuaternionNormalize(_transQuaternion);
	//
	//		//_mtxRotation = XMMatrixRotationQuaternion(_transQuaternion);
	//
	//		//_transFront = XMVector3TransformNormal(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), _mtxRotation);
	//		//_transRight = XMVector3TransformNormal(XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), _mtxRotation);
	//
	//		//313233 くぉ→マトリクス
	//		//_mtxRotationY = XMMatrixRotationY(XMConvertToRadians(ROTASION_SPEED));
	//		//_transFront = XMVector3TransformNormal(_transFront, _mtxRotationY);
	//		//_transRight = XMVector3TransformNormal(_transRight, _mtxRotationY);
	//		//_rotation.y += XMConvertToRadians(ROTASION_SPEED);
	//	}
	//
	//	if (CInput::GetKeyPress('J')) {
	//		XMVECTOR rotation = XMQuaternionRotationAxis(_transUp, -0.1f);
	//		_transQuaternion = XMQuaternionMultiply(_transQuaternion, rotation);
	//		_transQuaternion = XMQuaternionNormalize(_transQuaternion);
	//
	//		//_mtxRotation = XMMatrixRotationQuaternion(_transQuaternion);
	//
	//		//_transFront = XMVector3TransformNormal(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), _mtxRotation);
	//		//_transRight = XMVector3TransformNormal(XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), _mtxRotation);
	//	}
	//
	//	//ツール用処理仮
	//	{
	//		//正面
	//		XMFLOAT3 initPos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	//		if (CInput::GetKeyTrigger('1') || CInput::GetKeyTrigger(VK_NUMPAD1)) {
	//			SetCameraPosition(XMFLOAT3(0.0f, 0.0f, -100.0f));
	//			SetLookQuaternion(&_viewQuaternion, &initPos);
	//		}
	//
	//		//右面
	//		if (CInput::GetKeyTrigger('3') || CInput::GetKeyTrigger(VK_NUMPAD3)) {
	//			SetCameraPosition(XMFLOAT3(100.0f, 0.0f, 0.0f));
	//			SetLookQuaternion(&_viewQuaternion, &initPos);
	//		}
	//
	//		//真上
	//		if (CInput::GetKeyTrigger('7') || CInput::GetKeyTrigger(VK_NUMPAD7)) {
	//			SetCameraPosition(XMFLOAT3(0.0f, 100.0f, 0.0f));
	//			SetLookQuaternion(&_viewQuaternion, &initPos);
	//		}
	//
	//		//後ろ
	//		if ((CInput::GetKeyTrigger('1') || CInput::GetKeyTrigger(VK_NUMPAD1)) && CInput::GetKeyPress(VK_CONTROL)) {
	//			SetCameraPosition(XMFLOAT3(0.0f, 0.0f, 100.0f));
	//			SetLookQuaternion(&_viewQuaternion, &initPos);
	//		}
	//
	//		//左面
	//		if ((CInput::GetKeyTrigger('3') || CInput::GetKeyTrigger(VK_NUMPAD3)) && CInput::GetKeyPress(VK_CONTROL)) {
	//			SetCameraPosition(XMFLOAT3(-100.0f, 0.0f, 0.0f));
	//			SetLookQuaternion(&_viewQuaternion, &initPos);
	//		}
	//
	//		//真下
	//		if ((CInput::GetKeyTrigger('7') || CInput::GetKeyTrigger(VK_NUMPAD7)) && CInput::GetKeyPress(VK_CONTROL)) {
	//			SetCameraPosition(XMFLOAT3(0.0f, -100.0f, 0.0f));
	//			SetLookQuaternion(&_viewQuaternion, &initPos);
	//		}
	//	}
	//	
	//}
	
	/*if (CInput::GetKeyPress('Q')) {
		_rotation.y += 0.01f;
	}*/

	/*if (CInput::GetKeyPress('E')) {
		_rotation.y -= 0.01f;
	}*/

	_mtxRotation = XMMatrixRotationQuaternion(_transQuaternion);
	_transFront = XMVector3TransformNormal(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), _mtxRotation);
	_transRight = XMVector3TransformNormal(XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), _mtxRotation);

	/*if (Flag::GetGamePhase() == FLAG_TARGET_SELECT) {
 		this->Set(XMFLOAT3(50.0f, 50.0f, -50.0f), false, );
	}*/
	//選択したモードやスキルなどのカメラワークによって何か変える
	if (Flag::GetGamePhase() == FLAG_ACTION_SELECT) {
		//Accele(&_transRight, 0.1f);
		//SetLookQuaternion(&_transQuaternion, &CManager::GetScene()->GetGameObject<Player>(TYPE_PLAYER)->GetPosition());
		//SetLookQuaternion(&_viewQuaternion, &CManager::GetScene()->GetGameObject<Player>(TYPE_PLAYER)->GetPosition());
		
		//XMVECTOR rotation = XMQuaternionRotationAxis(_transUp, 0.001f);
		//_viewQuaternion = XMQuaternionMultiply(_viewQuaternion, rotation);
		//_viewQuaternion = XMQuaternionNormalize(_viewQuaternion);
		//
		//_mtxRotation = XMMatrixRotationQuaternion(_viewQuaternion);
		//
		//_transFront = XMVector3TransformNormal(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), _mtxRotation);
		//_transRight = XMVector3TransformNormal(XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), _mtxRotation);
	}
}



void CCamera::Draw()
{
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
	//m_InvViewMatrix = XMMatrixRotationRollPitchYaw(_rotation.x, _rotation.y, _rotation.z);
	_invViewMatrix = XMMatrixRotationQuaternion(_transQuaternion);	//エスコン風操作
	//_invViewMatrix = XMMatrixRotationQuaternion(_viewQuaternion);
	
	_invViewMatrix *= XMMatrixTranslation(_position.x, _position.y, _position.z);
	//_invViewMatrix *= XMMatrixRotationY(_atAngle);

	XMVECTOR det;
	m_ViewMatrix = XMMatrixInverse(&det, _invViewMatrix);

	CRenderer::SetViewMatrix(&m_ViewMatrix);

	// プロジェクションマトリクス設定
	m_ProjectionMatrix = XMMatrixPerspectiveFovLH(1.0f, dxViewport.Width / dxViewport.Height, 1.0f, 1500.0f);

	CRenderer::SetProjectionMatrix(&m_ProjectionMatrix);
}

void CCamera::SetHoming(XMFLOAT3 thisPos, XMFLOAT3 thatPos)
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

void CCamera::Accele(XMVECTOR* vector, float speed)
{
	_position.x += XMVectorGetX(*vector) * speed;
	_position.y += XMVectorGetY(*vector) * speed;
	_position.z += XMVectorGetZ(*vector) * speed;
}

XMVECTOR* CCamera::SetLookQuaternion(XMVECTOR* outQuaternion, XMFLOAT3* look)
{
	XMVECTOR x, y, z;
	XMMATRIX out = XMMatrixIdentity();
	XMFLOAT3 up = XMFLOAT3(0.0f, 1.0f, 0.0f);
	z = XMLoadFloat3(look) - XMLoadFloat3(&_position);
	z = XMVector3Normalize(z);
	y = XMVector3Normalize(XMLoadFloat3(&up));
	x = XMVector3Cross(y, z);
	x = XMVector3Normalize(x);
	//y = XMVector3Normalize(XMVector2Cross(x, y));

	out.r[0].m128_f32[0] = x.m128_f32[0]; out.r[0].m128_f32[1] = x.m128_f32[1]; out.r[0].m128_f32[2] = x.m128_f32[2]; out.r[0].m128_f32[3] = x.m128_f32[3];
	out.r[1].m128_f32[0] = y.m128_f32[0]; out.r[1].m128_f32[1] = y.m128_f32[1]; out.r[1].m128_f32[2] = y.m128_f32[2]; out.r[1].m128_f32[3] = y.m128_f32[3];
	out.r[2].m128_f32[0] = z.m128_f32[0]; out.r[2].m128_f32[1] = z.m128_f32[1]; out.r[2].m128_f32[2] = z.m128_f32[2]; out.r[2].m128_f32[3] = z.m128_f32[3];

	*outQuaternion = XMQuaternionRotationMatrix(out);	//マトリクス→Quaternion
	return outQuaternion;
}

void CCamera::SetQuaternion(XMVECTOR* outQuaternion, XMVECTOR inQuaternion)
{
	*outQuaternion = inQuaternion;
}

void CCamera::SetLookVector(XMVECTOR f, XMVECTOR r, XMVECTOR u)
{
	_transFront = f;
	_transRight = r;
	_transUp = u;
}
