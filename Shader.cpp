#include "main.h"
#include <io.h>
#include "renderer.h"
#include "Shader.h"

void Shader::Load(std::string fileName, D3D11_INPUT_ELEMENT_DESC input, int numElements)
{
	
}

void Shader::Set()
{
	//// 定数バッファ生成
	//D3D11_BUFFER_DESC hBufferDesc;
	//hBufferDesc.ByteWidth = sizeof(XMMATRIX);
	//hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	//hBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//hBufferDesc.CPUAccessFlags = 0;
	//hBufferDesc.MiscFlags = 0;
	//hBufferDesc.StructureByteStride = sizeof(float);

	//m_D3DDevice->CreateBuffer(&hBufferDesc, NULL, &m_WorldBuffer);
	//m_ImmediateContext->VSSetConstantBuffers(0, 1, &m_WorldBuffer);

	//m_D3DDevice->CreateBuffer(&hBufferDesc, NULL, &m_ViewBuffer);
	//m_ImmediateContext->VSSetConstantBuffers(1, 1, &m_ViewBuffer);

	//m_D3DDevice->CreateBuffer(&hBufferDesc, NULL, &m_ProjectionBuffer);
	//m_ImmediateContext->VSSetConstantBuffers(2, 1, &m_ProjectionBuffer);


	//hBufferDesc.ByteWidth = sizeof(MATERIAL);

	//m_D3DDevice->CreateBuffer(&hBufferDesc, NULL, &m_MaterialBuffer);
	//m_ImmediateContext->VSSetConstantBuffers(3, 1, &m_MaterialBuffer);


	//hBufferDesc.ByteWidth = sizeof(LIGHT);

	//m_D3DDevice->CreateBuffer(&hBufferDesc, NULL, &m_LightBuffer);
	//m_ImmediateContext->VSSetConstantBuffers(4, 1, &m_LightBuffer);





	//// 入力レイアウト設定
	//m_ImmediateContext->IASetInputLayout(m_VertexLayout);

	//// シェーダ設定
	//m_ImmediateContext->VSSetShader(m_VertexShader, NULL, 0);
	//m_ImmediateContext->PSSetShader(m_PixelShader, NULL, 0);



	//// ライト初期化
	//LIGHT light;
	//light.Direction = XMFLOAT4(0.0f, -1.0f, 0.0f, 0.0f);
	//light.Diffuse = COLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//light.Ambient = COLOR(0.1f, 0.1f, 0.1f, 1.0f);
	//SetLight(light);


	//// マテリアル初期化
	//MATERIAL material;
	//ZeroMemory(&material, sizeof(material));
	//material.Diffuse = COLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//material.Ambient = COLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//SetMaterial(material);
}
