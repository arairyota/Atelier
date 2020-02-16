#ifndef CAMERA_H
#define CAMERA_H

#define CAMERA_SPEED (1.5)

#define FRONT_INIT	(0.0f, 0.0f, 1.0f, 0.0f)
#define RIGHT_INIT	(1.0f, 0.0f, 0.0f, 0.0f)
#define UP_INIT		(0.0f, 1.0f, 0.0f, 0.0f)


#include "GameObject.h"
#include <list>

class CameraData;


class CCamera : public GameObject
{
private:
	RECT m_Viewport;

	XMMATRIX	_invViewMatrix;

	float _atAngle = 0.0f; //注視点回転用アングル

	float _len = 0.0f;

	XMMATRIX	m_ViewMatrix;
	XMMATRIX	_mtxRotationY;
	XMMATRIX	_mtxRotation;

	bool is_enable;

	XMVECTOR _transFront;
	XMVECTOR _transRight;
	XMVECTOR _transUp;

	XMVECTOR _viewFront;
	XMVECTOR _viewRight;
	XMVECTOR _viewUp;

	XMVECTOR _transQuaternion;
	XMVECTOR _viewQuaternion;

	std::list<CameraData*> _dataList;
	bool _first = true;
	int _frameCnt = 0;
	float _spherValue; //球面線形補間用値
	float _spherFrame; //球面線形補間用格納変数
	
	XMFLOAT3 _linerValue;

public:
	CCamera() {
		_transFront = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
		_transRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
		_transUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

		_transRight = XMVector3Cross(_transFront, _transUp);
		_transRight = XMVector3Normalize(_transRight);
		_transUp = XMVector3Normalize(_transUp);
		_transFront = XMVector3Normalize(_transFront);

		_viewRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
		_viewUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

		_viewRight = XMVector3Cross(_viewFront, _viewUp);
		_viewRight = XMVector3Normalize(_viewRight);
		_viewUp    = XMVector3Normalize(_viewUp);
		_viewFront = XMVector3Normalize(_viewFront);

		_mtxRotationY = XMMatrixIdentity();
		_mtxRotation = XMMatrixIdentity();
		_transQuaternion = XMQuaternionIdentity();
		_viewQuaternion = XMQuaternionIdentity();
	};
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void SetHoming(XMFLOAT3 thisPos, XMFLOAT3 ThatPos);
	void Accele(XMVECTOR* vector, float speed);

	void SetCameraPosition(XMFLOAT3 pos) { _position = pos; }
	XMVECTOR* SetLookQuaternion(XMVECTOR* outQuaternion, XMFLOAT3* look);
	XMVECTOR* RotationQuaternion();
	void SetQuaternion(XMVECTOR* outQuaternion, XMVECTOR inQuaternion);

	void SetTQuaternion(XMVECTOR inQ) { _transQuaternion = inQ; };

	XMVECTOR* GetViewQuaternion() { return &_viewQuaternion; }
	XMVECTOR* GetTransQuaternion() { return &_transQuaternion; }

	XMVECTOR GetFront() { return _viewFront; }
	XMVECTOR GetRight() { return _viewRight; }
	XMVECTOR GetUp() { return _viewUp; }

	void SetFront(XMVECTOR front) { _transFront = front; }
	void SetRight(XMVECTOR right) { _transRight = right; }
	void SetUp(XMVECTOR up) { _transUp = up; }

	void SetLookVector(XMVECTOR f, XMVECTOR r, XMVECTOR u);

	bool WayPointMove();
	XMFLOAT3 LinearInterpol(XMFLOAT3 start, XMFLOAT3 end, int frameCnt); //線形補間計算
	void SetCameraData(std::list<CameraData*> list) { _dataList = list; }

	XMFLOAT3 GetPosition() { return _position; }

	void read();

	XMMATRIX GetView() { return m_ViewMatrix; };
	XMFLOAT3 _position;
	XMFLOAT3 _rotation;
	bool is_Enable;
};

#endif // !CAMERA_H
