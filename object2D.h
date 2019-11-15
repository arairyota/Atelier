#ifndef OBJECT2D_H
#define OBJECT2D_H

#include "GameObject.h"

class Object2D : public GameObject{
protected:
	XMFLOAT2 _position;
	XMFLOAT2 _rotation;
	XMFLOAT2 _scale;

	XMMATRIX _world;

	VERTEX3D _vertex[4];

	ID3D11Buffer* _VertexBuffer = nullptr; //���_�o�b�t�@ 
	CTexture* _Texture = nullptr;			//�e�N�X�`��
public:
	Object2D() {
		_position = XMFLOAT2(0.0f, 0.0f);
		_rotation = XMFLOAT2(0.0f, 0.0f);
		_scale    = XMFLOAT2(0.0f, 0.0f);
	};
};

#endif // !OBJECT2D_H

