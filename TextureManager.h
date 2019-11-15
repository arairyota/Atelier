/*****************************************************************************
TextureManager.h
TextureManager.h
name	:�V�� �Ñ�
data	:2019/08/12 13:43:54
*****************************************************************************/
#ifndef TextureManager_H
#define TextureManager_H

//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "texture.h"

//////////////////////////////////////////////////////////////////////////////
//define��`
//////////////////////////////////////////////////////////////////////////////
#define TEXTURE_FILENAME_MAX (80)

//////////////////////////////////////////////////////////////////////////////
//�O���錾
//////////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////////
//TextureManager�N���X
//////////////////////////////////////////////////////////////////////////////
class TextureManager {
private:
	static TextureManager* _instance;
	std::vector<CTexture*> _textureList;

public:
	static void Create();
	static void Derete();
	static TextureManager* GetInstance();
	bool AllLoad();
	void AllUnLoad();

	CTexture* GetTexture(int index) {
		return _textureList[index];
	};

	unsigned int GetWidth(int index) {
		return _textureList[index]->GetWidth();
	}

	unsigned int GetHeight(int index) {
		return _textureList[index]->GetHeight();
	}

protected:

};

#endif // !TextureManager_H

//void Init();
//void Uninit();
//void Update();
//void Draw();
