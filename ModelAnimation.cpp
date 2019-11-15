#include "main.h"
#include "renderer.h"
#include "Timer.h"
#include "ModelAnimation.h"

void ModelAnimation::Update(int frame, int AnimType)
{
	aiAnimation* animation = _scene[AnimType]->mAnimations[0];
	for (int c = 0; c < animation->mNumChannels; c++) {
		aiNodeAnim* nodeAnim = animation->mChannels[c];

		//回転
		int f = frame % nodeAnim->mNumRotationKeys;
		_nodeRotation[nodeAnim->mNodeName.C_Str()] = nodeAnim->mRotationKeys[f].mValue;

		//移動
		f = frame % nodeAnim->mNumPositionKeys;
		_nodePosition[nodeAnim->mNodeName.C_Str()] = nodeAnim->mPositionKeys[f].mValue;
	}
}

void ModelAnimation::Update(int frame, int AnimType, int anim1, int anim2, int blend)
{
	//aiAnimation* animation = _scene[AnimType]->mAnimations[0];

	//aiAnimation* animation1 = _scene[0]->mAnimations[0];
	//aiAnimation* animation2 = _scene[1]->mAnimations[0];

	//for (int c = 0; c < animation1->mNumChannels; c++) {
	//	aiNodeAnim* nodeAnim = animation1->mChannels[c];

	//	aiNodeAnim* nodeAnim1 = animation1->mChannels[c];
	//	aiNodeAnim* nodeAnim2 = animation2->mChannels[c];

	//	//回転
	//	int f = frame % nodeAnim1->mNumRotationKeys;

	//	aiQuaternion::Interpolate(_nodeRotation[nodeAnim2->mNodeName.C_Str()], nodeAnim1->mRotationKeys[f].mValue, nodeAnim2->mRotationKeys[f].mValue, 1.0f) ; //Interpolate
	//	//_nodeRotation[nodeAnim1->mNodeName.C_Str()] = nodeAnim1->mRotationKeys[f].mValue;
	//	//移動
	//	f = frame % nodeAnim1->mNumPositionKeys;
	//	_nodePosition[nodeAnim1->mNodeName.C_Str()] = nodeAnim1->mPositionKeys[f].mValue;
	//}
}

void ModelAnimation::Draw(XMMATRIX Matrix)
{
	DrawMesh(_scene[0]->mRootNode, Matrix);
	_frame++;
}

void ModelAnimation::Load(const char * FileName)
{
	_scene[0] = aiImportFile("asset/HumanNeutral.fbx", aiProcessPreset_TargetRealtime_MaxQuality);
	_scene[1] = aiImportFile("asset/HumanSkill.fbx", aiProcessPreset_TargetRealtime_MaxQuality);
	//_scene[0] = aiImportFile(FileName, aiProcessPreset_TargetRealtime_MaxQuality);

	
	_meshNum = _scene[0]->mNumMeshes;

	_mesh = new MESH[_meshNum];

	for (int m = 0; m < _meshNum; m++) {
		aiMesh* mesh = _scene[0]->mMeshes[m];

		VERTEX3D* vertex = new VERTEX3D[mesh->mNumVertices];

		for (int i = 0; i < mesh->mNumVertices; i++) {
			vertex[i].Position = XMFLOAT3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
			vertex[i].Normal = XMFLOAT3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
			vertex[i].Diffuse = XMFLOAT4(1, 1, 1, 1);
			vertex[i].TexCoord = XMFLOAT2((float)mesh->mTextureCoords[0][i].x, (float)mesh->mTextureCoords[0][i].y);
		}

		//頂点バッファ生成
		{
			D3D11_BUFFER_DESC bd;
			ZeroMemory(&bd, sizeof(bd));
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(VERTEX3D) * mesh->mNumVertices;
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = 0;
			D3D11_SUBRESOURCE_DATA sd;
			ZeroMemory(&sd, sizeof(sd));
			sd.pSysMem = vertex;
			CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &_mesh[m]._vertexBuffer);
		}
		delete[] vertex;

		USHORT* index;
		index = new USHORT[mesh->mNumFaces * 3];

		for (int i = 0; i < mesh->mNumFaces; i++) {
			index[i * 3 + 0] = mesh->mFaces[i].mIndices[0];
			index[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
			index[i * 3 + 2] = mesh->mFaces[i].mIndices[2];


		}
		_mesh[m]._indexNum = mesh->mNumFaces * 3;

		{
			D3D11_BUFFER_DESC bd;
			ZeroMemory(&bd, sizeof(bd));
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(USHORT) * _mesh[m]._indexNum;
			bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
			bd.CPUAccessFlags = 0;

			D3D11_SUBRESOURCE_DATA sd;
			ZeroMemory(&sd, sizeof(sd));
			sd.pSysMem = index;
			CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &_mesh[m]._indexBuffer);
		}
		delete[] index;
	}

}

void ModelAnimation::Unload()
{
	for (int animNum = 0; animNum < ANIMATION_MAX; animNum++) {
		aiReleaseImport(_scene[animNum]);
	}
	for (int cnt = 0; cnt < _meshNum; cnt++) {
		_mesh[cnt]._vertexBuffer->Release();
		_mesh[cnt]._indexBuffer->Release();
	}

	//for(int m = 0; m < )
}

//Nodeがfbxの親子関係を表す

void ModelAnimation::DrawMesh(aiNode * Node, XMMATRIX Matrix)
{
	Update(_frame, _animIndex);
	aiMatrix4x4 matrix = Node->mTransformation; //親からみたマトリクス
	aiTransposeMatrix4(&matrix);

	aiQuaternion aiQuat = _nodeRotation[Node->mName.C_Str()];
	XMVECTOR quat = XMLoadFloat4(&XMFLOAT4(aiQuat.x, aiQuat.y, aiQuat.z, aiQuat.w));

	XMMATRIX world = XMMatrixRotationQuaternion(quat);

	aiVector3D aiPos = _nodePosition[Node->mName.C_Str()];
	world *= XMMatrixTranslation(aiPos.x, aiPos.y, aiPos.z);

	//XMMATRIX world = XMLoadFloat4x4((XMFLOAT4X4*)&matrix);
	world *= Matrix;	//親のマトリクス
	CRenderer::SetWorldMatrix(&world);

	for (int n = 0; n < Node->mNumMeshes; n++) {
		UINT m = Node->mMeshes[n]; //Meshの整理番号を受け取る
		//メッシュ描画 mを使う
		CRenderer::SetVertexBuffers(_mesh[m]._vertexBuffer);
		CRenderer::SetIndexBuffer(_mesh[m]._indexBuffer);
		CRenderer::DrawIndexed(_mesh[m]._indexNum, 0, 0);
	}

	//親の子供の数分だけ子供のポインタをもらう
	for (int i = 0; i < Node->mNumChildren; i++) {
		DrawMesh(Node->mChildren[i], world);	//再起呼び出し
	}
}

void ModelAnimation::ChangeAnimation(int index)
{
	_frame = 0;
	_animIndex = index;
}
