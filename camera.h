#ifndef CAMERA_H
#define CAMERA_H

#define CAMERA_SPEED (10)

#include "GameObject.h"


class CCamera : public GameObject
{
private:
	RECT m_Viewport;
	
	float RotZ = 0.0f;
	//float TransX = 0.0f;
	//float TransY = 50.0f;
	//float TransZ = -100.0f;

	float _atAngle = 0.0f; //注視点回転用アングル

	float _len = 0.0f;

	//XMFLOAT3 _position;
	//XMFLOAT3 _rotation;

	XMMATRIX	m_ViewMatrix;

	bool is_enable;

	XMVECTOR _transFront;
	XMVECTOR _transRight;
	XMVECTOR _transUp;

	XMVECTOR _ViewFront;
	XMVECTOR _ViewRight;
	XMVECTOR _ViewUp;

public:
	CCamera() {
		_transRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
		_transUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

		_transRight = XMVector3Cross(_transFront, _transUp);
		_transRight = XMVector3Normalize(_transRight);
		_transUp = XMVector3Normalize(_transUp);
		_transFront = XMVector3Normalize(_transFront);
	};
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void Set(XMFLOAT3 thisPos, XMFLOAT3 ThatPos);
	void Homing();

	XMMATRIX GetView() { return m_ViewMatrix; };
	XMFLOAT3 _position;
	XMFLOAT3 _rotation;
	bool is_Enable;
};

#endif // !CAMERA_H
