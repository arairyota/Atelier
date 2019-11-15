#include "main.h"
#include "texture.h"
#include "TextureManager.h"



TextureManager* TextureManager::_instance = nullptr;

void TextureManager::Create()
{
	if (_instance == nullptr) {
		_instance = new TextureManager;
		_instance->AllLoad();
	}
}

void TextureManager::Derete()
{
	if (_instance != nullptr) delete _instance;
}

bool TextureManager::AllLoad()
{

	for (int i = 0; i < TEXTURE_MAX; ++i) {
		
		_textureList.push_back(new CTexture(TextureData[i].filename, TextureData[i].width, TextureData[i].height));
		_textureList.back()->Load();
	}

	return true;
}

void TextureManager::AllUnLoad()
{
	for (auto it = _textureList.begin(); it != _textureList.end(); ++it) {
 		(*it)->Unload();
		delete (*it);
	}

	_textureList.clear();
}

TextureManager* TextureManager::GetInstance()
{
	if (_instance != nullptr) {
		return _instance;
	}
}
