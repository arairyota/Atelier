/*****************************************************************************
TextureManager.h
TextureManager.h
name	:新井 崚太
data	:2019/08/12 13:43:54
*****************************************************************************/
#ifndef TextureManager_H
#define TextureManager_H

//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include "texture.h"

//////////////////////////////////////////////////////////////////////////////
//define定義
//////////////////////////////////////////////////////////////////////////////
#define TEXTURE_FILENAME_MAX (80)

//////////////////////////////////////////////////////////////////////////////
//前方宣言
//////////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////////
//TextureManagerクラス
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
