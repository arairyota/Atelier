#ifndef BILLBOARD_H
#define BILLBOARD_H

#include "object3D.h"
#include "TextureManager.h"
#include "texture.h"

class Billboard : public object3D {
private:
	VERTEX3D _vertex[4];
	ID3D11Buffer* _VertexBuffer = NULL; //頂点バッファ 
	XMMATRIX _cameraView;
	XMFLOAT3 _transPos;		//ダメージエフェクト用

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void Set(XMFLOAT3 position, XMFLOAT3 scale, CTexture* texture);
	void DamegeNumEffect(XMFLOAT3 position, XMFLOAT3 scale, int texcoord, float transX);
};

#endif // !BILLBOARD_H