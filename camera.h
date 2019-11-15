#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.h"
#include "playerInterface.h"

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

	
public:
	CCamera() {};
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
