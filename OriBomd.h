/*****************************************************************************
OriBomd.h
OriBomd.h
name	:新井 崚太
data	:2019/08/12 12:49:05
*****************************************************************************/
#ifndef OriBomd_H
#define OriBomd_H

//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include "AttackItem.h"

//////////////////////////////////////////////////////////////////////////////
//define定義
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//前方宣言
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//OriBomdクラス
//////////////////////////////////////////////////////////////////////////////
class OriBomd : public AttackItem{
private:

public:
	OriBomd() { _atk = 50.0f; _attribute = Fire; _num = 5; };
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void Use(XMFLOAT3 position)override;

protected:

};

#endif // !OriBomd_H

//void Init();
//void Uninit();
//void Update();
//void Draw();
