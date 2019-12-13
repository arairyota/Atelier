/*****************************************************************************
template.h
DamegeNumEffectFactory.h
name	:新井 崚太
data	:2019/11/22 11:12:12
*****************************************************************************/
#ifndef DamegeNumEffectFactory_H
#define DamegeNumEffectFactory_H

//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//define定義
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//前方宣言
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//DamegeNumEffectFactoryクラス
//////////////////////////////////////////////////////////////////////////////
class DamegeNumEffectFactory {
private:
	static DamegeNumEffectFactory* _instance;

public:
	static void CreateInstance();
	

	static void Delete();

	static DamegeNumEffectFactory* GetInstance();

	void CreateEffect(XMFLOAT3 position, int numDamege);
};

#endif // !DamegeNumEffectFactory_H

