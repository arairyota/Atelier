/*****************************************************************************
ItemPoach.h
ItemPoach.h
name	:新井 崚太
data	:2019/08/12 12:18:01
*****************************************************************************/
#ifndef ItemPoach_H
#define ItemPoach_H

//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include "polygon.h"

//////////////////////////////////////////////////////////////////////////////
//define定義
//////////////////////////////////////////////////////////////////////////////
#define ITEMPOACH_MAX	(25)
#define INIT_XMFLOAT2	(XMFLOAT2(0.0f, 0.0f))



//////////////////////////////////////////////////////////////////////////////
//前方宣言
//////////////////////////////////////////////////////////////////////////////
class ItemBase;

//////////////////////////////////////////////////////////////////////////////
//ItemPoachクラス
//////////////////////////////////////////////////////////////////////////////
class ItemPoach : public CPolygon{
private:
	std::vector<ItemBase*>_ItemPoachList;
	//CPolygon* _polygonPoach[ITEMPOACH_MAX];
	

	unsigned int _select;
	short int _waitFrame = 0;

	CPolygon* _cursor;
public:
	ItemPoach() { _waitFrame = 0; };
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void Set(XMFLOAT2 position, XMFLOAT2 rotation, XMFLOAT2 scale, XMMATRIX mtx, CTexture* texture)override;
	XMFLOAT2 GetPos()override { return _position; };
	void Translation(XMMATRIX mtx, XMFLOAT2 position) {
		_world = mtx;
		_position = position;
	};

	ItemBase* GetSelectItem();

protected:

};

#endif // !ItemPoach_H

//void Init();
//void Uninit();
//void Update();
//void Draw();
