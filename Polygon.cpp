#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "texture.h"
#include "polygon.h"

void CPolygon::Init()
{
	_vertex[0].Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	_vertex[0].Normal   = XMFLOAT3(0.0f, 0.0f, 0.0f);
	_vertex[0].Diffuse  = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	_vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);	//�e�N�X�`�����W
	
	_vertex[1].Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	_vertex[1].Normal   = XMFLOAT3(0.0f, 0.0f, 0.0f);
	_vertex[1].Diffuse  = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	_vertex[1].TexCoord = XMFLOAT2(0.0f, 0.0f);
	
	_vertex[2].Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	_vertex[2].Normal   = XMFLOAT3(0.0f, 0.0f, 0.0f);
	_vertex[2].Diffuse  = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	_vertex[2].TexCoord = XMFLOAT2(0.0f, 0.0f);
	
	_vertex[3].Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	_vertex[3].Normal   = XMFLOAT3(0.0f, 0.0f, 0.0f);
	_vertex[3].Diffuse  = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	_vertex[3].TexCoord = XMFLOAT2(0.0f, 0.0f);

	_Texture = nullptr;
}

void CPolygon::Uninit()
{
	if (_VertexBuffer == nullptr) return;
	_VertexBuffer->Release();
}

void CPolygon::Update()
{

}

void CPolygon::Draw()
{
	
		UINT stride = sizeof(VERTEX3D);
		UINT offset = 0;

		CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &_VertexBuffer, &stride, &offset); //���_�o�b�t�@�ݒ�
		CRenderer::SetTexture(_Texture); //�e�N�X�`���ݒ�
		
		
		CRenderer::SetWorldViewProjection2D(_position, _rotation, _scale, _world); //2D�}�g���N�X�ݒ�
		CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP); //�g�|���W�ݒ�@���_�����ԃ��[��
		CRenderer::GetDeviceContext()->Draw(4, 0); //�|���S���`��@�i���_��, �ǂ����璸�_��邩�j
	
}

void CPolygon::Set(XMFLOAT2 position, XMFLOAT2 rotation, XMFLOAT2 scale, XMMATRIX mtx, CTexture* texture)
{
	_position = position;
	_rotation = rotation;
	_scale = scale;
	_world = mtx;
	_world.r[0].m128_f32[0] = 1.0f;

	_world.r[1].m128_f32[1] = 1.0f;
	_world.r[2].m128_f32[2] = 1.0f;
	_Texture = texture;
	float SizeX = _Texture->GetWidth() / 2;
	float SizeY = _Texture->GetHeight() / 2;

	_vertex[0].Position = XMFLOAT3(-SizeX, -SizeY, 0.0f);
	_vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	_vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	_vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);	//�e�N�X�`�����W

	_vertex[1].Position = XMFLOAT3(SizeX, -SizeY, 0.0f);
	_vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	_vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	_vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	_vertex[2].Position = XMFLOAT3(-SizeX, SizeY, 0.0f);
	_vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	_vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	_vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	_vertex[3].Position = XMFLOAT3(SizeX, SizeY, 0.0f);
	_vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	_vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	_vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	D3D11_BUFFER_DESC bd; //�o�b�t�@�f�[�^
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX3D) * 4; //
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA sd; //�T�u���\�[�X�f�[�^
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = _vertex;
	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &_VertexBuffer);
}

void CPolygon::SetLeftToRight(XMFLOAT2 position, XMFLOAT2 rotation, XMFLOAT2 scale, XMMATRIX mtx, CTexture* texture)
{
	_position = position;
	_rotation = rotation;
	_scale = scale;
	_world = mtx;

	_world.r[0].m128_f32[0] = 1.0f;
	_world.r[1].m128_f32[1] = 1.0f;
	_world.r[2].m128_f32[2] = 1.0f;
	_Texture = texture;

	

	_vertex[0].Position = XMFLOAT3(0.0f, -0.5f, 0.0f);
	_vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	_vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	_vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);	//�e�N�X�`�����W

	_vertex[1].Position = XMFLOAT3(1.0f, -0.5f, 0.0f);
	_vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	_vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	_vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	_vertex[2].Position = XMFLOAT3(0.0f, 0.5f, 0.0f);
	_vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	_vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	_vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	_vertex[3].Position = XMFLOAT3(1.0f, 0.5f, 0.0f);
	_vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	_vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	_vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	D3D11_BUFFER_DESC bd; //�o�b�t�@�f�[�^
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX3D) * 4; //
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA sd; //�T�u���\�[�X�f�[�^
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = _vertex;
	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &_VertexBuffer);
}
