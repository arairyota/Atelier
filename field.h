#ifndef FIELD_H
#define FIELD_H

#include <d3d11.h>
#include "object3D.h"
class CTexture;

#define FIELD_WIDTH (300)

class Field : public object3D{
private:
	ID3D11Buffer* _VertexBuffer = NULL; //���_�o�b�t�@ 
	CTexture* _Texture = NULL;			//�e�N�X�`��

public:
	void Init(float posX, float posY, float posZ);
	void Uninit();
	void Update();
	void Draw();
};

#endif // !FIELD_H
