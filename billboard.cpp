#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "TextureManager.h"
#include "texture.h"
#include "billboard.h"

#include "object3D.h"
#include "camera.h"
#include "scene.h"

void Billboard::Init()
{
	_position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	_rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	_scale    = XMFLOAT3(1.0f, 1.0f, 1.0f);

	_vertex[0].Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	_vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	_vertex[0].Diffuse = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	_vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);	//テクスチャ座標

	_vertex[1].Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	_vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	_vertex[1].Diffuse = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	_vertex[1].TexCoord = XMFLOAT2(0.0f, 0.0f);

	_vertex[2].Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	_vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	_vertex[2].Diffuse = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	_vertex[2].TexCoord = XMFLOAT2(0.0f, 0.0f);

	_vertex[3].Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	_vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	_vertex[3].Diffuse = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	_vertex[3].TexCoord = XMFLOAT2(0.0f, 0.0f);

	_Texture = nullptr;

	//頂点データ
	D3D11_BUFFER_DESC bd; //バッファデータ
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(VERTEX3D) * 4; //頂点数
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd; //サブリソースデータ
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = _vertex;
	
	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &_VertexBuffer);
}

void Billboard::Uninit()
{
	//_Texture->Unload();
	//delete _Texture;
}

void Billboard::Update()
{

}

void Billboard::Draw()
{
	char debugStr[256];
	
	//debugStr = world.r[0].m128_f32[0];

	

	XMMATRIX world;
	Scene* scene = CManager::GetScene();
	UINT stride = sizeof(VERTEX3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &_VertexBuffer, &stride, &offset); //頂点バッファ設定
	CRenderer::SetTexture(_Texture); //テクスチャ設定
	CCamera* camera = scene->GetGameObject<CCamera>(TYPE_CAMERA);

	_cameraView = XMMatrixTranspose(camera->GetView());

	world = XMMatrixIdentity();

	_cameraView.r[0].m128_f32[3] = 0.0f;
	_cameraView.r[1].m128_f32[3] = 0.0f;
	_cameraView.r[2].m128_f32[3] = 0.0f;

	world = _cameraView;
	world *= XMMatrixScaling(_scale.x, _scale.y, _scale.z);
	
	world *= XMMatrixTranslation(_position.x, _position.y, _position.z);
	//world *= XMMatrixRotationRollPitchYaw(_rotation.x, _rotation.y, _rotation.z);
	
	CRenderer::SetWorldMatrix(&world);
	//sprintf("%f", world.r[0].m128_f32[0]);
	//OutputDebugString();

	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP); //トポロジ設定　頂点を結ぶルール
	CRenderer::GetDeviceContext()->Draw(4, 0); //ポリゴン描画　（頂点数, どこから頂点やるか）
}

void Billboard::Set(XMFLOAT3 position, XMFLOAT3 scale, CTexture* texture)
{
	_position = position;
	//_rotation = rotation;
	_scale = scale;
	_Texture = texture;

	_vertex[0].Position = XMFLOAT3(-0.5f, 0.5f, 0.0f);
	_vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	_vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	_vertex[0].TexCoord = XMFLOAT2(0, 0);	//テクスチャ座標

	_vertex[1].Position = XMFLOAT3(0.5f, 0.5f, 0.0f);
	_vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	_vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	_vertex[1].TexCoord = XMFLOAT2(1, 0);

	_vertex[2].Position = XMFLOAT3(-0.5f, -0.5f, 0.0f);
	_vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	_vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	_vertex[2].TexCoord = XMFLOAT2(0, 1);

	_vertex[3].Position = XMFLOAT3(0.5f, -0.5f, 0.0f);
	_vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	_vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	_vertex[3].TexCoord = XMFLOAT2(1, 1);

	//頂点データ
	//D3D11_BUFFER_DESC bd; //バッファデータ
	//ZeroMemory(&bd, sizeof(bd));
	//bd.ByteWidth = sizeof(VERTEX3D) * 4; //頂点数
	//bd.Usage = D3D11_USAGE_DEFAULT;
	//bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//bd.CPUAccessFlags = 0;

	//D3D11_SUBRESOURCE_DATA sd; //サブリソースデータ
	//ZeroMemory(&sd, sizeof(sd));
	//sd.pSysMem = _vertex;
	//
	//CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &_VertexBuffer);

	//頂点バッファの上書き
	D3D11_MAPPED_SUBRESOURCE msr;
	CRenderer::GetDeviceContext()->Map(_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	memcpy(msr.pData, _vertex, sizeof(VERTEX3D) * 4);
	CRenderer::GetDeviceContext()->Unmap(_VertexBuffer, 0);
}
