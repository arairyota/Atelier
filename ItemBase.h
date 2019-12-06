/*****************************************************************************
ItemBase.h
ItemBase.h
name	:新井 崚太
data	:2019/08/12 12:21:33
*****************************************************************************/
#ifndef ItemBase_H
#define ItemBase_H

//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include "object3D.h"
#include "polygon.h"

//////////////////////////////////////////////////////////////////////////////
//define定義
//////////////////////////////////////////////////////////////////////////////
#define ITEM_TYPE_ATTACK	(0x01)
#define ITEM_TYPE_HEEL		(0x02)


//////////////////////////////////////////////////////////////////////////////
//前方宣言
//////////////////////////////////////////////////////////////////////////////
class CTexture;
class Billboard;


//////////////////////////////////////////////////////////////////////////////
//ItemBaseクラス
//////////////////////////////////////////////////////////////////////////////
class ItemBase : public object3D {
private:
	XMFLOAT2 position2D;

public:
	ItemBase() {
		_scale = XMFLOAT3(2.0f, 2.0f, 2.0f);
	};

	CTexture* GetTexture() {
		return _Texture;
	}

	CPolygon* GetPolygon() {
		return _polygon;
	}

	void SetPolygon(CPolygon* polygon) {
		_polygon = polygon;
	}

	void SetPosition2D(float x, float y) {
		position2D = XMFLOAT2(x, y);
		
	}

	virtual void Use(XMFLOAT3 position)=0;	//アイテム使用
protected:
	
	int _num;	//今何個か
	CPolygon* _polygon; //2Dポリゴン
	Billboard* _billboard;
};

#endif // !ItemBase_H

//void Init();
//void Uninit();
//void Update();
//void Draw();
