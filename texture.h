#ifndef TEXTURE_H
#define TEXTURE_H

#include "renderer.h"

#define TEXTURE_FILENAME_MAX (80)

typedef struct TextureFile_tag
{
	const char filename[TEXTURE_FILENAME_MAX];
	int width;		//画像全体の大きさX
	int height;		//Y
	//int wpattern;	//何パターンあるかX
	//int hpattern;	//Y
	//int oneCharSize;//1文字の大きさ
}TextureFile;	//

enum TEXTURE
{
	ITEM,
	FIELD,
	SKILL,
	ATTACK,
	NUMBER,
	ORIBOMD,
	ITEMPOACH,
	CURSOR,
	REDBAR,
	CHAR_UI_BASE,
	BLACKBAR,
	GROUND,
	TITLELOGO,

	TEXTURE_MAX,
};

const TextureFile TextureData[TEXTURE_MAX] = {
	{"asset/itemIcon.tga", 200, 100,},
	{"asset/field004.tga", 0, 0,},
	{"asset/skill.tga"   , 200, 100,},
	{"asset/attack.tga"  , 200, 100,},
	{"asset/number.tga"  , 320, 32},
	{"asset/OriBomd.tga" , 100, 100},
	{"asset/ItemPoach.tga", 500, 500},
	{"asset/Cursor.tga"  , 100, 100},
	{"asset/RedBar.tga", 32, 32},
	{"asset/CharacterUIBase.tga", 400, 128},
	{"asset/BlackBar.tga", 32, 32},
	{"asset/ground.tga", 32, 32},
	{"asset/TitleLogo.tga", 5000, 3000}
};

class CTexture
{
private:
	

	const std::string _filename;
	int _width;									//画像全体の大きさX
	int _height;								//Y

public:
	CTexture() {};
	CTexture(const std::string name, int width, int height) : _filename(name), _width(width), _height(height) {}
	void Load();
	void Load(std::string name);
	void Unload();

	ID3D11ShaderResourceView* GetShaderResourceView(){ return m_ShaderResourceView; }

	float GetWidth() { return _width; }
	float GetHeight() { return _height; }
	//XMFLOAT2 GetTexturePixSize(int index);	//引数の値のピクセル数を返す
private:

	ID3D11Texture2D*			m_Texture;
	ID3D11ShaderResourceView*	m_ShaderResourceView;
};

#endif // !TEXTURE_H