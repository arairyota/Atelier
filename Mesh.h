#ifndef MESH_H
#define MESH_H

#include "Object3D.h"
#include "texture.h"

#define INIT_SIZE_X (60)
#define INIT_SIZE_Z (60)
#define INIT_GRID_NUM_X (50)
#define INIT_GRID_NUM_Z (50)
#define UV_X (float)(1.0f/4.0f)
#define UV_Y (float)(1.0f/3.0f)
#define UV_LEFT_X (float)(0)
#define UV_LEFT_Y (float)(1.0f)
#define UV_RIGHT_X (float)(2.0f)
#define UV_RIGHT_Y (float)(1.0f)
#define UV_FLONT_X (1)
#define UV_FLONT_Y (1)

#include "object3D.h"

class Mesh : public object3D {
public:
	ID3D11Buffer* _VertexBuffer = NULL; //頂点バッファ 
	ID3D11Buffer* _IndexBuffer = NULL;
	WORD* _pIndex;

	float _sizeX;
	float _sizeZ;
	int _numX;
	int _numZ;
	int _vertexNum;
	int _indexNum;
	int _gridNumX;
	int _gridNumZ;
	int _primitivNum;
	float _texUvX, _texUvY; //テクスチャのUV 1メッシュあたりどれくらいの大きさか
	VERTEX3D* _pVertex;
	WORD* _FirstIndex;

	XMFLOAT3 va;
	XMFLOAT3 vb;

	XMFLOAT3 n;
};

#endif // !MESH
