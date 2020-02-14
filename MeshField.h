#ifndef MESHFIELD_H
#define MESHFIELD_H

#include "Mesh.h"

class MeshField  : public Mesh{
public:
	MeshField(){};
	void Init();
	void Uninit(void);
	void Update(void) {};
	void Draw(void);
	void Set(float SizeX, float SizeZ, int GridNumX, int GridNumZ);

	float GetHeight(XMFLOAT3 position);

	void SetDrawing(bool flag) { _isDraw = flag; }

public:
	ID3D11Buffer* _VertexBuffer = NULL; //���_�o�b�t�@ 
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
	float _texUvX, _texUvY; //�e�N�X�`����UV 1���b�V��������ǂꂭ�炢�̑傫����
	VERTEX3D* _pVertex;
	WORD* _FirstIndex;

	XMFLOAT3 va;
	XMFLOAT3 vb;

	XMFLOAT3 n;

	bool _isDraw;
};

#endif // !MESHFIELD_H