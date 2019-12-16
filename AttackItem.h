/*****************************************************************************
AttackItem.h
AttackItem.h
name	:新井 崚太
data	:2019/08/12 12:40:15
*****************************************************************************/
#ifndef AttackItem_H
#define AttackItem_H

//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include "ItemBase.h"

//////////////////////////////////////////////////////////////////////////////
//define定義
//////////////////////////////////////////////////////////////////////////////
#define ITEM_SPEED_FRAME (90)

//////////////////////////////////////////////////////////////////////////////
//enum
//////////////////////////////////////////////////////////////////////////////
enum AttributeIndex
{
	None,
	Fire,
	Ice,
	Thunder,
};


//////////////////////////////////////////////////////////////////////////////
//前方宣言
//////////////////////////////////////////////////////////////////////////////
class CCamera;

//////////////////////////////////////////////////////////////////////////////
//AttackItemクラス
//////////////////////////////////////////////////////////////////////////////
class AttackItem : public ItemBase {
private:
	
public:
	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Use(XMFLOAT3 position, GameActor* user)=0;
protected:
	float _atk;
	AttributeIndex _attribute;
	XMFLOAT3 _len; //敵との距離
	CCamera* _camera;
};

#endif // !AttackItem_H

//void Init();
//void Uninit();
//void Update();
//void Draw();
