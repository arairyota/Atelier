#include "main.h"
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/matrix4x4.h>
#include "renderer.h"
#include "SkinMeshModel.h"

#include "Animation.h"

void Animation::Load(aiAnimation* animation, std::unordered_map<std::string, unsigned int> boneMapping)
{
	_name = animation->mName.C_Str();				//アニメーションの名前
	_ticksParSecond = animation->mTicksPerSecond;	//フレームレート
	_duration = animation->mDuration;				//フレーム数
	_channelNum = animation->mNumChannels;			//そのアニメーションの動くボーンの数

	for (UINT cn = 0; cn < _channelNum; cn++) {
		aiNodeAnim* aiChannel = animation->mChannels[cn];
		UINT boneIndex = boneMapping[aiChannel->mNodeName.C_Str()];
		NodeAnim* channel = &_channelArray[boneIndex];

		//アニメーション行列
		channel->matrix = new XMMATRIX[(int)_duration];
		for (UINT amn = 0; amn < (UINT)_duration; amn++) {
			aiQuaternion quat = aiChannel->mRotationKeys[amn % aiChannel->mNumRotationKeys].mValue;
			aiVector3D pos = aiChannel->mPositionKeys[amn % aiChannel->mNumPositionKeys].mValue;
			//スケール入れてもおｋ

			aiMatrix4x4 mtx = aiMatrix4x4({ 1.0f, 1.0f, 1.0f }, quat, pos);
			channel->matrix[amn] = {
				mtx.a1, mtx.a2, mtx.a3, mtx.a4,
				mtx.b1, mtx.b2, mtx.b3, mtx.b4,
				mtx.c1, mtx.c2, mtx.c3, mtx.c4,
				mtx.d1, mtx.d2, mtx.d3, mtx.d4
			};
		}
	}
}

void Animation::SetAnimation(Node* node, BONE* boneArray, int frame, XMMATRIX* parentMatrix)
{
	BONE* bone = &boneArray[node->boneIndex];
	XMMATRIX worldMatrix = (*parentMatrix);
	if (_channelArray.find(node->boneIndex) != _channelArray.end()) {
		worldMatrix *= _channelArray[node->boneIndex].matrix[(int)(frame * _ticksParSecond / 60.0f) % (UINT)_duration];
		bone->Matrix = worldMatrix;
		bone->Matrix *= bone->OffsetMatrix;

		for (UINT cn = 0; cn < node->childNum; cn++) {
			SetAnimation(&node->children[cn], boneArray, frame, &worldMatrix);
		}
		
	}

}

void Animation::Unload()
{
	for (auto& channel : _channelArray) {
		delete[] channel.second.matrix;
	}
	_channelArray.clear();
}
