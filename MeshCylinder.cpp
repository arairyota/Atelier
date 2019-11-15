#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "MeshCylinder.h"


void MeshCylinder::Init(float SizeX, float SizeZ, int GridNumX, int GridNumZ)
{
	_gridNumX = GridNumX;
	_gridNumZ = GridNumZ;
	_rotation.z = PI / 2;

	_vertexNum = (_gridNumX + 1) * (_gridNumZ + 1);
	_indexNum = (_gridNumX + 1) * (_gridNumZ * 2) + (_gridNumZ - 1) * 2;
	_primitivNum = _gridNumX * GridNumX * 2 + (_gridNumZ - 1) * 4;

	int cntX = 0;
	int VertexCnt = 0;

	_pIndex = new WORD[_indexNum];
	_pVertex = new VERTEX3D[_vertexNum];
	_FirstIndex = _pIndex;

	for (int cntZ = 0; cntZ < _gridNumZ; cntZ++) {
		for (cntX = 0; cntX < _gridNumX + 1; cntX++) {
			_pIndex[0] = (WORD)((GridNumX + 1) * (cntZ + 1) + cntX);
			_pIndex[1] = (WORD)((GridNumX + 1) * cntZ + cntX);

			_pIndex += 2;
		}

		if (cntZ < GridNumZ - 1) {
			cntX--;
			_pIndex[0] = (GridNumX + 1) * (WORD)cntZ + (WORD)cntX;
			_pIndex[1] = _pIndex[0] + (WORD)GridNumX + 2;
			_pIndex += 2;
		}
	}



	float FullSize = SizeX * GridNumX;

	//VERTEX3D* pVertex = new VERTEX3D[_vertexNum];

	for (int cntZ = 0; cntZ < GridNumZ + 1; cntZ++) {
		for (int cntX = 0; cntX < GridNumX + 1; cntX++) {
			_pVertex[VertexCnt].Position = XMFLOAT3((SizeX * cntX) - FullSize * 0.5f, 0, -(SizeZ * cntZ) + FullSize * 0.5f);
			_pVertex[VertexCnt].Normal = XMFLOAT3(0, 1, 0);
			_pVertex[VertexCnt].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			_pVertex[VertexCnt].TexCoord = XMFLOAT2((float)cntX, (float)cntZ);
			VertexCnt++;
		}
	}


	//頂点データ
	D3D11_BUFFER_DESC bd; //バッファデータ
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(VERTEX3D) * _vertexNum; //頂点数
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;


	D3D11_SUBRESOURCE_DATA sd; //サブリソースデータ
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = _pVertex;

	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &_VertexBuffer);


	//インデックスデータ
	D3D11_BUFFER_DESC indexDesc; //バッファデータ
	ZeroMemory(&indexDesc, sizeof(indexDesc));
	indexDesc.ByteWidth = sizeof(WORD) * _indexNum; //indexの数
	indexDesc.Usage = D3D11_USAGE_DEFAULT;
	indexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexDesc.CPUAccessFlags = 0;


	D3D11_SUBRESOURCE_DATA indexData; //サブリソースデータ
	ZeroMemory(&indexData, sizeof(indexData));
	indexData.pSysMem = _FirstIndex;

	CRenderer::GetDevice()->CreateBuffer(&indexDesc, &indexData, &_IndexBuffer);

	_Texture = new CTexture("asset/field004.tga", 0, 0);
	_Texture->Load();
}

void MeshCylinder::Uninit()
{
	_VertexBuffer->Release();
	_IndexBuffer->Release();
	_Texture->Unload();
	delete _Texture;
}

void MeshCylinder::Draw()
{
	UINT strides = sizeof(VERTEX3D);
	UINT offsets = 0;

	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &_VertexBuffer, &strides, &offsets); //頂点バッファ設定
	CRenderer::GetDeviceContext()->IASetIndexBuffer(_IndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	CRenderer::SetTexture(_Texture); //テクスチャ設定

									 //３D用
	XMMATRIX world;
	world = XMMatrixScaling(_scale.x, _scale.y, _scale.z);
	world *= XMMatrixRotationRollPitchYaw(_rotation.x, _rotation.y, _rotation.z);
	world *= XMMatrixTranslation(_position.x, _position.y, _position.z);
	CRenderer::SetWorldMatrix(&world);

	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP); //トポロジ設定　頂点を結ぶルール
	CRenderer::GetDeviceContext()->DrawIndexed(_indexNum, 0, 0); //ポリゴン描画　（頂点数, どこから頂点やるか）
}
