#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "GameObject.h"

class CTexture;
class CModel;

class object3D : public GameObject {
protected:
	XMFLOAT3 _position;
	XMFLOAT3 _rotation;
	XMFLOAT3 _scale;

	XMVECTOR _front;
	XMVECTOR _right;
	XMVECTOR _up;

	XMMATRIX _mtxRotationY;
	VERTEX3D _vertex[4];

	
	CModel* _model = NULL;
	

public:
	object3D() {
		_front = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
		_right = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
		_up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

		_right = XMVector3Cross(_front, _up);
		_right = XMVector3Normalize(_right);
		_up = XMVector3Normalize(_up);
		_front = XMVector3Normalize(_front);
	};

	XMFLOAT3 GetPosition() { return _position; };
};

#endif // !OBJECT_H
