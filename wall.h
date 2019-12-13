#ifndef WALL_H
#define WALL_H

#include <d3d11.h>
#include "texture.h"

#define FIELD_WIDTH (300)

class Wall {
private:
	ID3D11Buffer* _VertexBuffer = NULL; //���_�o�b�t�@ 
	CTexture* _Texture = NULL;			//�e�N�X�`��

public:
	void Init(float posX, float posY, float posZ);
	void Uninit();
	void Update();
	void Draw(float posX, float posY, float posZ, float RotX, float RotY, float RotZ);
};


#endif // !WALL_H
