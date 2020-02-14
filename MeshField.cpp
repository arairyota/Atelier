#include "main.h"
#include "renderer.h"
#include "object3D.h"
#include "TextureManager.h"
#include "Mesh.h"
#include "MeshField.h"


void MeshField::Init()
{
	//HRESULT hr;

	_position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	_rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	_scale = XMFLOAT3(10.0f, 10.0f, 10.0f);

	_gridNumX = 0;
	_gridNumZ = 0;
	
	_vertexNum   = 0;
	_indexNum    = 0;
	_primitivNum = 0;

	_pIndex = nullptr;
	_pVertex = nullptr;
	_FirstIndex = nullptr;

	
	_Texture = nullptr;
	//_Texture->Load("asset/field004.tga");
	_isDraw = false;
}

void MeshField::Uninit()
{
	_VertexBuffer->Release();
	_IndexBuffer->Release();
	
}

void MeshField::Draw(void)
{
	if (!_isDraw) return;
	UINT strides = sizeof(VERTEX3D);
	UINT offsets = 0;

	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &_VertexBuffer, &strides, &offsets); //���_�o�b�t�@�ݒ�
	CRenderer::GetDeviceContext()->IASetIndexBuffer(_IndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	CRenderer::SetTexture(_Texture); //�e�N�X�`���ݒ�

									 //�RD�p
	XMMATRIX world;
	world = XMMatrixScaling(_scale.x, _scale.y, _scale.z);
	world = XMMatrixRotationRollPitchYaw(_rotation.x, _rotation.y, _rotation.z);
	world *= XMMatrixTranslation(_position.x, _position.y, _position.z);
	CRenderer::SetWorldMatrix(&world);
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP); //�g�|���W�ݒ�@���_�����ԃ��[��
	CRenderer::GetDeviceContext()->DrawIndexed(_indexNum, 0, 0); //�|���S���`��@�i���_��, �ǂ����璸�_��邩�j
}

void MeshField::Set(float SizeX, float SizeZ, int GridNumX, int GridNumZ)
{
	_gridNumX = GridNumX;
	_gridNumZ = GridNumZ;

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

	for (float cntZ = 0; cntZ < GridNumZ + 1; cntZ++) {
		for (int cntX = 0; cntX < GridNumX + 1; cntX++) {
			_pVertex[VertexCnt].Position = XMFLOAT3((SizeX * cntX) - FullSize * 0.5f, rand() % 5 + 1 - 5.0f, -(SizeZ * cntZ) + FullSize * 0.5f);
			_pVertex[VertexCnt].Normal = XMFLOAT3(0, 1, 0);
			_pVertex[VertexCnt].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			_pVertex[VertexCnt].TexCoord = XMFLOAT2((float)cntX, (float)cntZ);
			VertexCnt++;
		}
	}

	//�@���x�N�g�������߂�
	for (int cntZ = 1; cntZ < GridNumZ - 1; cntZ++) {
		for (int cntX = 1; cntX < GridNumX - 1; cntX++) {
			va.x = _pVertex[(cntZ - 1) * GridNumX + cntX].Position.x - _pVertex[(cntZ + 1) * GridNumX + cntX].Position.x;
			va.y = _pVertex[(cntZ - 1) * GridNumX + cntX].Position.y - _pVertex[(cntZ + 1) * GridNumX + cntX].Position.y;
			va.z = _pVertex[(cntZ - 1) * GridNumX + cntX].Position.z - _pVertex[(cntZ + 1) * GridNumX + cntX].Position.z;

			vb.x = _pVertex[cntZ * GridNumX + (cntX + 1)].Position.x - _pVertex[(cntZ - 1) * GridNumX + (cntX - 1)].Position.x;
			vb.y = _pVertex[cntZ * GridNumX + (cntX + 1)].Position.y - _pVertex[(cntZ - 1) * GridNumX + (cntX - 1)].Position.y;
			vb.z = _pVertex[cntZ * GridNumX + (cntX + 1)].Position.z - _pVertex[(cntZ - 1) * GridNumX + (cntX - 1)].Position.z;

			n.x = va.y * vb.z - va.z * vb.y;
			n.y = va.z * vb.x - va.x * vb.z;
			n.z = va.x * vb.y - va.y * vb.x;

			float len = sqrtf(n.x * n.x + n.y * n.y + n.z * n.z);

			n.x = n.x / len;
			n.y = n.y / len;
			n.z = n.z / len;

			_pVertex[cntZ * GridNumX + 1 + cntX].Normal = n;
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

	_Texture = TextureManager::GetInstance()->GetTexture(GROUND);
}

//�v���C���[�̍��W���牺�����ɂ����蔻����o���Ă����W�l�����Ԃ�
float MeshField::GetHeight(XMFLOAT3 position)
{
	int x, z;
	XMFLOAT3 p0, p1, p2, v01, v02, n, v, hp, va, vb;
	float dp0n, dvn, dpn, t;

	v = XMFLOAT3(0.0f, -10.0f, 0.0f); //�������������ׂ��

	//1�O���b�h���̃T�C�Y GridSize ���_���S�̏ꍇ�����Ōv�Z �ǂ���mesh�ɏ���Ă��邩
	x = ( position.x + (INIT_SIZE_X * INIT_GRID_NUM_X) / 2) / INIT_SIZE_X; // pos.x /0.1
	z = (-position.z + (INIT_SIZE_Z * INIT_GRID_NUM_Z) / 2) / INIT_SIZE_Z;

	if (position.x < -25) {
		int a = 0;
	}

	//�n�_�ƏI�_����n�_vector
	va.x = _pVertex[(z + 1) * (INIT_GRID_NUM_X + 1) + (x + 1)].Position.x - _pVertex[z * (INIT_GRID_NUM_X + 1) + x].Position.x;
	va.y = _pVertex[(z + 1) * (INIT_GRID_NUM_X + 1) + (x + 1)].Position.y - _pVertex[z * (INIT_GRID_NUM_X + 1) + x].Position.y;
	va.z = _pVertex[(z + 1) * (INIT_GRID_NUM_X + 1) + (x + 1)].Position.z - _pVertex[z * (INIT_GRID_NUM_X + 1) + x].Position.z;

	vb.x = position.x - _pVertex[z * (INIT_GRID_NUM_Z + 1) + x].Position.x;
	vb.y = position.y - _pVertex[z * (INIT_GRID_NUM_Z + 1) + x].Position.y;
	vb.z = position.z - _pVertex[z * (INIT_GRID_NUM_Z + 1) + x].Position.z;

	//1���b�V���̂ǂ����̎O�p�|���S���̏�ɂ��邩
	if (va.z * vb.x - va.x * vb.z > 0.0f) { //y�����̌��ʂ��v���X�������獶���̎O�p�`else
		p0 = _pVertex[(z + 1) * (INIT_GRID_NUM_X + 1) + x].Position;


		p1 = _pVertex[z * (INIT_GRID_NUM_X + 1) + x].Position;
		p2 = _pVertex[(z + 1) * (INIT_GRID_NUM_X + 1) + (x + 1)].Position;
	}
	else {
		p0 = _pVertex[z * (INIT_GRID_NUM_X + 1) + (x + 1)].Position;
		p1 = _pVertex[(z + 1) * (INIT_GRID_NUM_X + 1) + (x + 1)].Position;//����̍��W
		p2 = _pVertex[z * (INIT_GRID_NUM_X + 1) + x].Position;//�E���̍��W
	}

	//��̃x�N�g�������߂�p0��p1
	v01.x = p1.x - p0.x;
	v01.y = p1.y - p0.y;
	v01.z = p1.z - p0.z;

	//p0��p2
	v02.x = p2.x - p0.x;
	v02.y = p2.y - p0.y;
	v02.z = p2.z - p0.z;

	n.x = v01.y * v02.z - v01.z * v02.y;
	n.y = v01.z * v02.x - v01.x * v02.z;
	n.z = v01.x * v02.y - v01.y * v02.x;

	dvn = v.x * n.x + v.y * n.y + v.z * n.z;
	dp0n = p0.x * n.x + p0.y * n.y + p0.z * n.z;
	dpn = position.x * n.x + position.y * n.y + position.z * n.z;

	t = (dp0n - dpn) / dvn;
	hp.x = position.x + v.x * t;
	hp.y = position.y + v.y * t;
	hp.z = position.z + v.z * t;

	return hp.y;
}
