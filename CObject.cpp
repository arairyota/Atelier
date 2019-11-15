////=============================================================================
////
//// オブジェクトの処理 [CObject.cpp]
////
////=============================================================================
//#include <d3d11.h>
//#include "main.h"
//#include "CObject.h"
//
//std::list<CObject*> CObject::ObjectList;	//クラスにstatic変数があることを明記
//
//CObject::CObject()
//{
//	_position = {0.0f, 0.0f, 0.0f};
//	is_Display = true;
//
//	ObjectList.push_back(this); //this=自分自身のポインタ(CObjectのポインタを指す)
//}
//
//void CObject::Init(XMFLOAT3 pos)
//{
//	//_position = XMFLOAT3(0.0f, 0.0f, 0.0f);
//	
//	
//}
//
//void CObject::Update()
//{
//	
//}
//
//void CObject::Draw()
//{
//	
//}
//
//void CObject::UpdateAll()
//{
//	//cnt = イテレーター
//	for (auto cnt = ObjectList.begin(); cnt != ObjectList.end(); ++cnt) {
//		CObject* work = *cnt; //イテレーターからObjectのアドレスをもらう
//		work->Update();
//		
//	}
//
//	for (auto cnt = ObjectList.begin(); cnt != ObjectList.end();) {
//		CObject* work = *cnt;
//		for (auto cnt2 = std::next(cnt, 1); cnt2 != ObjectList.end(); cnt2++) {
//			CObject* work2 = *cnt2;
//			/*if (CCollision::Collision(work, work2)) {
//				work->is_Display = false;
//			}*/
//		}
//		if (!work->is_Display) {
//			delete work;
//			cnt = ObjectList.erase(cnt);
//		}
//		else cnt++;
//	}
//}
//
//void CObject::DrawAll()
//{
//	for (auto cnt = ObjectList.begin(); cnt != ObjectList.end(); ++cnt) {
//		CObject* work = *cnt; //イテレーターからObjectのアドレスをもらう
//		work->Draw();
//	}
//}
//
//void CObject::Destroy()
//{
//	is_Display = false;
//}
//
//bool CObject::GetDestroy(void)
//{
//	return is_Destroy;
//}
