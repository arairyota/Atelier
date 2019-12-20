/*****************************************************************************
ModelAnimation.h
ModelAnimation.h
name	:�V�� �Ñ�
data	:2019/09/04 10:25:55
*****************************************************************************/
#ifndef ModelAnimation_H
#define ModelAnimation_H

//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/cimport.h>
#include <assimp/matrix4x4.h>
#include <map>

struct MESH {
	ID3D11Buffer* _vertexBuffer;
	ID3D11Buffer* _indexBuffer;
	UINT _indexNum;
};

//////////////////////////////////////////////////////////////////////////////
//define��`
//////////////////////////////////////////////////////////////////////////////
#define ANIMATION_MAX (3)
//////////////////////////////////////////////////////////////////////////////
//�O���錾
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//ModelAnimation�N���X
//////////////////////////////////////////////////////////////////////////////
class ModelAnimation {
private:
	MESH* _mesh;	//���I�z��
	UINT _meshNum;
	const aiScene* _scene[ANIMATION_MAX];
	std::map<std::string, aiQuaternion> _nodeRotation;
	std::map<std::string, aiVector3D> _nodePosition;
	int _animIndex = 0;
	UINT _frame;

	//ID3D11Buffer* _vertexBuffer;
	//ID3D11Buffer* _indexBuffer;
	//UINT _indexNum;

public:
	ModelAnimation() { _animIndex = 0; _frame = 0; };
	void Update(int frame, int AnimType);
	void Update(int frame, int animType, int anim1, int anim2, int blend);
	void Draw(XMMATRIX Matrix);
	void Load();
	void Load(const char* FileName);
	void Unload();
	void DrawMesh(aiNode* Node, XMMATRIX Matrix);
	void ChangeAnimation(int index);

protected:

};

#endif // !ModelAnimation_H

//void Init();
//void Uninit();
//void Update();
//void Draw();
