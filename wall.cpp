#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "polygon.h"
#include "field.h"
#include "wall.h"

void Wall::Init(float posX, float posY, float posZ)
{
	VERTEX3D vertex[4];
	vertex[0].Position = XMFLOAT3(posX, posY, posZ + FIELD_WIDTH);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);	//�e�N�X�`�����W

	vertex[1].Position = XMFLOAT3(posX + 300.0f, posY, posZ + FIELD_WIDTH);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(posX + 0.0f, posY, posZ);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(posX + 300.0f, posY, posZ);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	D3D11_BUFFER_DESC bd; //�o�b�t�@�f�[�^
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX3D) * 4; //
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA sd; //�T�u���\�[�X�f�[�^
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;
	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &_VertexBuffer);
	_Texture = new CTexture();
	_Texture->Load("asset/field004.tga");
}

void Wall::Uninit()
{
	_VertexBuffer->Release();
	_Texture->Unload();
	delete _Texture;
}

void Wall::Update()
{
	
}

void Wall::Draw(float posX, float posY, float posZ, float RotX, float RotY, float RotZ)
{



	UINT stride = sizeof(VERTEX3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &_VertexBuffer, &stride, &offset); //���_�o�b�t�@�ݒ�
	CRenderer::SetTexture(_Texture); //�e�N�X�`���ݒ�

	//�RD �����̃}�g���b�N�X
	XMMATRIX world;
	XMMATRIX RotationX, RotationY, RotationZ;
	XMMATRIX Trans;
	world = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	world *= XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);
	world *= XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	RotationX = XMMatrixRotationX(RotX);
	RotationY = XMMatrixRotationY(RotY);
	RotationZ = XMMatrixRotationZ(RotZ);
	Trans = XMMatrixTranslation(posX, posY, posZ);
	world *= RotationX;
	world *= RotationY;
	world *= RotationZ;
	world *= Trans;
	CRenderer::SetWorldMatrix(&world);

	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP); //�g�|���W�ݒ�@���_�����ԃ��[��
	CRenderer::GetDeviceContext()->Draw(4, 0); //�|���S���`��@�i���_��, �ǂ����璸�_��邩�j
}
