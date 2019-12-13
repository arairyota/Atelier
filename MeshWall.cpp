#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "Mesh.h"
#include "MeshWall.h"


void MeshWall::Init()
{
	_position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	_rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	_scale    = XMFLOAT3(0.0f, 0.0f, 0.0f);
	_gridNumX = 0;
	_gridNumZ = 0;
	//_rotation.z = PI / 2;

	_vertexNum   = 0;
	_indexNum    = 0;
	_primitivNum = 0;

	_texUvX = 0.0f;
	_texUvY = 0.0f;

	_pIndex = nullptr;
	_pVertex = nullptr;
	_FirstIndex = nullptr;

	_Texture = nullptr;
	//_Texture->Load("asset/MeshBox.tga");
}

void MeshWall::Uninit()
{
	_VertexBuffer->Release();
	_IndexBuffer->Release();
	_Texture->Unload();
	delete _Texture;
}

void MeshWall::Draw()
{
	UINT strides = sizeof(VERTEX3D);
	UINT offsets = 0;

	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &_VertexBuffer, &strides, &offsets); //���_�o�b�t�@�ݒ�
	CRenderer::GetDeviceContext()->IASetIndexBuffer(_IndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	CRenderer::SetTexture(_Texture); //�e�N�X�`���ݒ�

									 //�RD�p
	XMMATRIX world;
	world = XMMatrixScaling(_scale.x, _scale.y, _scale.z);
	world *= XMMatrixRotationRollPitchYaw(_rotation.x, _rotation.y, _rotation.z);
	world *= XMMatrixTranslation(_position.x, _position.y, _position.z);
	CRenderer::SetWorldMatrix(&world);

	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP); //�g�|���W�ݒ�@���_�����ԃ��[��
	CRenderer::GetDeviceContext()->DrawIndexed(_indexNum, 0, 0); //�|���S���`��@�i���_��, �ǂ����璸�_��邩�j
}

void MeshWall::Set(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scale, float SizeX, float SizeZ, float GridNumX, float GridNumZ, float uvX, float uvY)
{
	_position.x = pos.x;
	_position.y = pos.y;
	_position.z = pos.z;

	_rotation.x = rot.x;
	_rotation.y = rot.y;
	_rotation.z = rot.z;

	_scale.x = scale.x;
	_scale.y = scale.y;
	_scale.z = scale.z;

	_gridNumX = GridNumX;
	_gridNumZ = GridNumZ;
	//_rotation.z = PI / 2;

	_vertexNum = (_gridNumX + 1) * (_gridNumZ + 1);
	_indexNum = (_gridNumX + 1) * (_gridNumZ * 2) + (_gridNumZ - 1) * 2;
	_primitivNum = _gridNumX * GridNumX * 2 + (_gridNumZ - 1) * 4;

	_texUvX = (float)(1.0f / (GridNumX * 4.0f));
	_texUvY = (float)(1.0f / (GridNumZ * 3.0f));

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
			_pVertex[VertexCnt].TexCoord = XMFLOAT2((uvX * UV_X) + cntX * _texUvX, (uvY * UV_Y) + cntZ * _texUvY);
			VertexCnt++;
		}
	}


	//���_�f�[�^
	D3D11_BUFFER_DESC bd; //�o�b�t�@�f�[�^
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(VERTEX3D) * _vertexNum; //���_��
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;


	D3D11_SUBRESOURCE_DATA sd; //�T�u���\�[�X�f�[�^
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = _pVertex;

	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &_VertexBuffer);


	//�C���f�b�N�X�f�[�^
	D3D11_BUFFER_DESC indexDesc; //�o�b�t�@�f�[�^
	ZeroMemory(&indexDesc, sizeof(indexDesc));
	indexDesc.ByteWidth = sizeof(WORD) * _indexNum; //index�̐�
	indexDesc.Usage = D3D11_USAGE_DEFAULT;
	indexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexDesc.CPUAccessFlags = 0;


	D3D11_SUBRESOURCE_DATA indexData; //�T�u���\�[�X�f�[�^
	ZeroMemory(&indexData, sizeof(indexData));
	indexData.pSysMem = _FirstIndex;

	CRenderer::GetDevice()->CreateBuffer(&indexDesc, &indexData, &_IndexBuffer);

	_Texture = new CTexture("asset/field004.tga", 0, 0);
	_Texture->Load();
}