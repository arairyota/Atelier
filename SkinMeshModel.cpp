#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/matrix4x4.h>

#include "main.h"
#include "renderer.h"
#include "TextureManager.h"

#include "SkinMeshModel.h"
using std::unordered_map;

SkinMeshModel::SkinMeshModel(std::string name, GameObject* parent, bool active)
{
	// 入力レイアウト生成
	D3D11_INPUT_ELEMENT_DESC inputDesc[] =
	{
		{ "POSITION",	0,	DXGI_FORMAT_R32G32B32_FLOAT,	0,	D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0,	D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0,	D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0,	D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BONE_NUM",	0,	DXGI_FORMAT_R32G32B32A32_UINT,	0,	D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BONE_INDEX",	0,	DXGI_FORMAT_R32G32B32A32_FLOAT,	0,	D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	//ShaderManager::GetInstance().Load("ModelAnimation", inputDesc, 7);
}

void SkinMeshModel::Load(const char* filePath)
{
	//読み込み
	AnimModel_Vertex3D* vertexArray = nullptr;
	unsigned int* indexArray = nullptr;
	unsigned int vertexNum = 0;
	unsigned int indexNum = 0;

	//ファイルパス作成
	std::string path = filePath; //パス
	size_t pos = path.find_last_of("/");
	path = path.substr(0, pos);

	//データの読み込み
	const aiScene* scene = nullptr;
	scene = aiImportFile(filePath, aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_ConvertToLeftHanded);
	assert(scene != nullptr && "モデルが読み込めません");

	//要素数
	_materialNum = scene->mNumMaterials;					//マテリアル数
	_textureNum = scene->mNumMaterials;						//テクスチャの数
	_subsetNum = scene->mNumMeshes;							//メッシュの数

	for (UINT mn = 0; mn < _subsetNum; mn++) {
		aiMesh* mesh = scene->mMeshes[mn];
		vertexNum += mesh->mNumVertices;					//メッシュの数
		for (UINT fn = 0; fn < mesh->mNumFaces; fn++) {
			indexNum += mesh->mFaces[fn].mNumIndices;		//インデックスの数
		}
	}

	//メモリ確保
	vertexArray = new AnimModel_Vertex3D[vertexNum];
	indexArray = new unsigned int[indexNum];
	_subsetArray = new AnimModelSubset[_subsetNum];

	//assimpからデータを読み込み
	unsigned int vc = 0;	//頂点カウント
	unsigned int ic = 0;	//インデックスカウント

	//ノード探索
	assert(scene->mRootNode != nullptr && "ルートノードがない");
	_node = new Node;
	LoadNode(_node, scene->mRootNode);

	//マテリアルデータ
	if (scene->HasMaterials()) {
		//作業用
		aiColor4D color;
		aiMaterial* material;
		aiString texName;

		//読み込み開始
		_materialNum = scene->mNumMaterials;
		_materialArray = new MATERIAL[_materialNum];
		_textureArray = new CTexture* [_materialNum];

		for (UINT i = 0; i < _materialNum; i++) {
			material = scene->mMaterials[i];
			aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &color);
			_materialArray[i].Ambient.r = color.r;
			_materialArray[i].Ambient.g = color.g;
			_materialArray[i].Ambient.b = color.b;
			_materialArray[i].Ambient.a = color.a;

			//ディフューズ
			aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &color);
			_materialArray[i].Diffuse.r = color.r;
			_materialArray[i].Diffuse.g = color.g;
			_materialArray[i].Diffuse.b = color.b;
			_materialArray[i].Diffuse.a = color.a;

			//エミッシブ
			aiGetMaterialColor(material, AI_MATKEY_COLOR_EMISSIVE, &color);
			_materialArray[i].Emission.r = color.r;
			_materialArray[i].Emission.g = color.g;
			_materialArray[i].Emission.b = color.b;
			_materialArray[i].Emission.a = color.a;

			//スペキュラー
			aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &color);
			_materialArray[i].Specular.r = color.r;
			_materialArray[i].Specular.g = color.g;
			_materialArray[i].Specular.b = color.b;
			_materialArray[i].Specular.a = color.a;

			//スペキュラ強度
			aiGetMaterialFloat(material, AI_MATKEY_SHININESS, &_materialArray[i].Shininess);

			//テクスチャ
			material->GetTexture(aiTextureType_DIFFUSE, 0, &texName);
			if (texName.length) {
				std::string texPath = path;
				texPath += "/";
				texPath += texName.C_Str();

			
				_textureArray[i] = TextureManager::GetInstance()->GetTexture(ORIBOMD); //テクスチャマネージャから呼び出す
			}
			else
			{
				_textureArray[i] = nullptr;
			}
		}
	}

	//サブセットデータ
	for (UINT sn = 0; sn < _subsetNum; sn++) {
		aiMesh* mesh = scene->mMeshes[sn];
		_subsetArray[sn].startIndex = ic;
		_subsetArray[sn].indexNum = 0;

		//マテリアル
		if (_materialArray != nullptr) {
			_subsetArray[sn].Material = &_materialArray[mesh->mMaterialIndex];
		}

		//テクスチャ
		if (_textureArray != nullptr) {
			if (_textureArray[mesh->mMaterialIndex]->GetWidth() != 0) {
				_subsetArray[sn].Texture = _textureArray[mesh->mMaterialIndex];
			}
			else {
				_subsetArray[sn].Texture = nullptr;
			}
		}

		//ボーン
		if (mesh->mNumBones > 0) {
			for (UINT bn = 0; bn < mesh->mNumBones; bn++) {
				aiBone* aibone = mesh->mBones[bn];
				aiMatrix4x4 offset = aibone->mOffsetMatrix;
				_boneList[_boneMapping[aibone->mName.C_Str()]].OffsetMatrix = {
					offset.a1, offset.a2, offset.a3, offset.a4,
					offset.b1, offset.b2, offset.b3, offset.b4,
					offset.c1, offset.c2, offset.c3, offset.c4,
					offset.d1, offset.d2, offset.d3, offset.d4

				};

				//頂点に対応ボーンのインデックスとweight付け
				for (UINT wn = 0; wn < aibone->mNumWeights; wn++) {
					vertexArray[vc + aibone->mWeights[wn].mVertexId].boneWeight[vertexArray[vc + aibone->mWeights[wn].mVertexId].boneNum]
						= aibone->mWeights[wn].mWeight;

					vertexArray[vc + aibone->mWeights[wn].mVertexId].boneIndex[vertexArray[vc + aibone->mWeights[wn].mVertexId].boneNum]
						= _boneMapping[aibone->mName.C_Str()];

					vertexArray[vc + aibone->mWeights[wn].mVertexId].boneNum++;
				}
			}
		}
	}

	//ボーン配列に格納
	_boneArray = new BONE[_boneNum];
	for (UINT i = 0; i < _boneNum; i++) {
		_boneArray[i] = _boneList[i];
	}

	//バッファ作成
	HRESULT hr;
	
	//頂点バッファ
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(AnimModel_Vertex3D) * vertexNum;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = vertexArray;

		hr = CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &_vertexBuffer);
		assert(SUCCEEDED(hr));
	}

	//インデックスバッファ
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(unsigned int) * indexNum;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = vertexArray;

		hr = CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &_indexBuffer);
		assert(SUCCEEDED(hr));
	}

	//ボーンバッファ
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(BONE) * _boneNum;
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.StructureByteStride = sizeof(float);

		hr = CRenderer::GetDevice()->CreateBuffer(&bd, nullptr, &_boneBuffer);
		assert(SUCCEEDED(hr));
	}

	//アニメーション読み込み

	//メモリ開放
	delete[] vertexArray;
	delete[] indexArray;
	_boneMapping.clear();
	_boneList.clear();

}

void SkinMeshModel::Unload()
{
	UnLoadNode(_node);

	if (_vertexBuffer != nullptr) {
		_vertexBuffer->Release();
		_vertexBuffer = nullptr;
	}

	if (_indexBuffer != nullptr) {
		_indexBuffer->Release();
		_indexBuffer = nullptr;
	}

	if (_boneBuffer != nullptr) {
		_boneBuffer->Release();
		_boneBuffer = nullptr;
	}

	if (_boneArray != nullptr) {
		delete[] _boneArray;
		_boneArray = nullptr;
	}

	if (_subsetArray != nullptr) {
		delete[] _subsetArray;
		_subsetArray = nullptr;
	}

	if (_textureArray != nullptr) {
		delete[] _textureArray;
		_textureArray = nullptr;
	}

	if (_materialArray != nullptr) {
		delete[] _materialArray;
		_materialArray = nullptr;
	}
}

void SkinMeshModel::Draw()
{
	//頂点バッファ設定
	CRenderer::SetVertexBuffers(_vertexBuffer); //引数なんかサイズ違うらしい

	//インデックスバッファ
	CRenderer::SetIndexBuffer(_indexBuffer);

	//ボーンバッファ設定
	if (_boneNum != 0) {
		CRenderer::GetDeviceContext()->UpdateSubresource(_boneBuffer, 0, nullptr, _boneArray, 0, 0);
		CRenderer::SetBoneBuffer(_boneBuffer);
	}

	//メッシュ描画
	for (UINT i = 0; i < _subsetNum; i++) {
		//マテリアル設定
		if (_subsetArray[i].Material != nullptr) {
			CRenderer::SetBoneBuffer(_boneBuffer);
		}

		//テクスチャ設定
		if (_subsetArray[i].Texture != nullptr) {
			CRenderer::SetTexture(_subsetArray[i].Texture);
		}

		//ポリゴン描画
		CRenderer::DrawIndexed(_subsetArray[i].indexNum, _subsetArray[i].startIndex, 0);
	}
}

void SkinMeshModel::LoadNode(Node* node, aiNode* ainode)
{
	//ノードの名前
	node->name = ainode->mName.C_Str();

	//ボーンの作成
	if (_boneMapping.find(node->name.c_str()) == _boneMapping.end()) {
		_boneMapping[node->name] = _boneNum;
		_boneList[_boneMapping[node->name]].OffsetMatrix = XMMatrixIdentity();
		_boneList[_boneMapping[node->name]].Matrix = XMMatrixIdentity();
		_boneNum++;
	}
	node->boneIndex = _boneMapping[node->name];

	//要素数
	node->childNum = ainode->mNumChildren;

	//子供の探索
	if (node->childNum > 0) {
		node->children = new Node[node->childNum];
		for (UINT cn = 0; cn < node->childNum; cn++) {
			node->children[cn].parent = node;
			LoadNode(&node->children[cn], ainode->mChildren[cn]);
		}
	}
}

void SkinMeshModel::UnLoadNode(Node* node)
{
	if (node->childNum > 0) {
		for (UINT cn = 0; cn < node->childNum; cn++) {
			UnLoadNode(&node->children[cn]);
		}
		delete[] node->children;
	}

	if (node->parent == nullptr) {
		delete node;
	}
}
