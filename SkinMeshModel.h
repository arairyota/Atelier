/*****************************************************************************
template.h
SkinMeshModel.h
name	:�V�� �Ñ�
data	:2019/12/23 10:59:32
*****************************************************************************/
#ifndef SkinMeshModel_H
#define SkinMeshModel_H

//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
//#include <string>
#include <list>
#include <unordered_map>
#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;


//#include "main.h"


//////////////////////////////////////////////////////////////////////////////
//define��`
//////////////////////////////////////////////////////////////////////////////
constexpr auto NUM_VERTEX_BONE_INFO = (4);	//static const�I�T���V���O

//�\����
struct AnimModel_Vertex3D
{
	XMFLOAT3		position;
	XMFLOAT3		normal;
	COLOR			color;
	XMFLOAT2		texCoode;
	int				boneNum = 0;
	unsigned int	boneIndex[NUM_VERTEX_BONE_INFO];
	float			boneWeight[NUM_VERTEX_BONE_INFO];
};

struct AnimModelSubset
{
	unsigned int startIndex;
	unsigned int indexNum;
	MATERIAL*		Material;
	CTexture* Texture;
};

struct Node
{
	std::string name;
	unsigned int boneIndex;
	Node* parent; //�e
	Node* children;
	unsigned int childNum;
};

//////////////////////////////////////////////////////////////////////////////
//�O���錾
//////////////////////////////////////////////////////////////////////////////
class GameObject;
class Animation;
class aiNode;
class CTexture;

//////////////////////////////////////////////////////////////////////////////
//SkinMeshModel�N���X
//////////////////////////////////////////////////////////////////////////////
class SkinMeshModel {
public:
	SkinMeshModel(std::string name, GameObject* parent, bool active = true);
	~SkinMeshModel() {};
	//bool Init();
	void Load(const char* filePath);
	void Unload();
	void Update();
	void Draw();

private:
	void LoadNode(Node* node, aiNode* ainode);
	void UnLoadNode(Node* node);

	ID3D11Buffer* _vertexBuffer = nullptr;
	ID3D11Buffer* _indexBuffer = nullptr;
	ID3D11Buffer* _boneBuffer = nullptr;

	Node* _node = nullptr;
	AnimModelSubset* _subsetArray = nullptr; //array�z��
	unsigned int _subsetNum = 0; 
	CTexture** _textureArray = nullptr;
	unsigned int _textureNum = 0;
	MATERIAL* _materialArray = nullptr;
	unsigned int _materialNum = 0;
	std::unordered_map<std::string, unsigned int> _boneMapping;
	std::unordered_map<unsigned int, BONE> _boneList;
	BONE* _boneArray = nullptr;
	unsigned int _boneNum = 0;
	Animation* _animation = nullptr;
};

#endif // !SkinMeshModel_H

