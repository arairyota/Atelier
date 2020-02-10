/*****************************************************************************
CamearEditor.h
CamearEditor.h
name	:新井 崚太
data	:2019/12/27 15:48:37
*****************************************************************************/
#ifndef CamearEditor_H
#define CamearEditor_H

//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include <list>
#include "CameraData.h"

//////////////////////////////////////////////////////////////////////////////
//define定義
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//前方宣言
//////////////////////////////////////////////////////////////////////////////
class CCamera;
class CameraData;

//////////////////////////////////////////////////////////////////////////////
//CamearEditorクラス
//////////////////////////////////////////////////////////////////////////////
class CamearEditor{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void Save();
	void DataClear();

private:
	CCamera* _camera;
	CameraData* _defaultCamera;
	std::list<CameraData*> _cameraDataList;
	CameraData* _data = nullptr;
	int _radio = 0;

	void DefaultCameraDataInit();	//デフォルトカメラデータ初期化

	bool _isEnable = true;

	char _fileName[64] = "";

protected:

};

#endif // !CamearEditor_H

//void Init();
//void Uninit();
//void Update();
//void Draw();
