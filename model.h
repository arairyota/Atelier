#ifndef CMODEL_H
#define CMODEL_H

#define NOMINMAX
#include <windows.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/cimport.h>
#include <assimp/matrix4x4.h>

#include "Object3D.h"

// マテリアル構造体
struct MODEL_MATERIAL : public object3D
{
	char						Name[256];
	MATERIAL					Material;
	char						TextureName[256];
};

// 描画サブセット構造体
struct SUBSET
{
	unsigned short	StartIndex;
	unsigned short	IndexNum;
	MODEL_MATERIAL	Material;
};

// モデル構造体
struct MODEL
{
	VERTEX3D		*VertexArray;
	unsigned short	VertexNum;
	unsigned short	*IndexArray;
	unsigned short	IndexNum;
	SUBSET			*SubsetArray;
	unsigned short	SubsetNum;
};



class CModel
{
private:
	ID3D11Buffer*	m_VertexBuffer = NULL;
	ID3D11Buffer*	m_IndexBuffer = NULL;

	DX11_SUBSET*	m_SubsetArray = NULL;
	unsigned short	m_SubsetNum;

	void LoadObj( const char *FileName, MODEL *Model );
	void LoadMaterial( const char *FileName, MODEL_MATERIAL **MaterialArray, unsigned short *MaterialNum );

	bool _isEnable = true;

public:
	void Draw();

	void Load( const char *FileName );
	void Unload();

	void SetEnable(bool b) { _isEnable = b; };

};

#endif // !CMODEL_H
