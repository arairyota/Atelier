////=============================================================================
////
//// オブジェクトの処理 [CObject.h]
////
////=============================================================================
//#ifndef _COBJECT_H_
//#define _COBJECT_H_
//
//#include <string>
//#include <list>
//#include <typeinfo>
//#include <d3d11.h>
//#include "main.h"
//
////=============================================================================
//// オブジェクトクラス
////=============================================================================
//class CObject
//{
//public:
//	CObject::CObject();
//	~CObject() {};
//
//	virtual const type_info&GetType() { return typeid(CObject); };
//
//	void Init(XMFLOAT3 pos);
//	virtual void Update(void);
//	void Draw(void);
//	void Uninit(void) {}
//	static void UpdateAll(void);
//	static void DrawAll(void);
//	void Destroy(void);
//	
//
//	bool GetDestroy(void);
//
//protected:
//	XMFLOAT3 _position;
//	XMFLOAT3 _rotation;
//	XMFLOAT3 _scale;
//	
//	bool	is_Display;		// 非表示フラグ
//	bool	is_Destroy;
//
//	static std::list<CObject*> ObjectList; //オブジェクト管理
//};
//
//#endif
