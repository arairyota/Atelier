/*****************************************************************************
template.h
Animation.h
name	:新井 崚太
data	:2019/12/24 10:35:26
*****************************************************************************/
#ifndef Animation_H
#define Animation_H

//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;
#include <string>
#include <unordered_map>
#include "main.h"

//////////////////////////////////////////////////////////////////////////////
//define定義
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//前方宣言
//////////////////////////////////////////////////////////////////////////////
struct aiAnimation;
struct BONE;
struct Node;


struct NodeAnim {
	XMMATRIX* matrix;

};
//////////////////////////////////////////////////////////////////////////////
//Animationクラス
//////////////////////////////////////////////////////////////////////////////
class Animation {
public:
	//アニメーションのマトリクスを読み込む
	void Load(aiAnimation* animation, std::unordered_map<std::string, unsigned int> boneMapping);
	void SetAnimation(Node* node, BONE* boneArray, int frame, XMMATRIX* parentMatrix);
	void Unload();

private:
	std::string _name;
	std::unordered_map<unsigned int, NodeAnim> _channelArray;
	unsigned int _channelNum = 0;
	double _duration = 0.0f;
	double _ticksParSecond = 0.0f;
};

#endif // !Animation_H

