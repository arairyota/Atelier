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

//構造体
struct SelectData
{
	CameraData* _data = nullptr;
	std::list<CameraData*>::iterator _it;
	bool _isDelete = false;
};

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
	//CameraData* _data = nullptr;
	SelectData* _selectData; //消去処理作るために仕方なく作った変数
	int _radio = 0;

	void DefaultCameraDataInit();	//デフォルトカメラデータ初期化

	bool _isEnable = true;

	char _fileName[64] = "";

	//std::vector<CameraData> _listv;
	CameraData _listv[100];


	//プライベート関数
	void EditorModeMenu();
	void EditorMenu();
	void FileMenu();
	void OperationMenu();
	void PresetMenu();
	void ReservationErase(); //消去予約

protected:

};

#endif // !CamearEditor_H

//void Init();
//void Uninit();
//void Update();
//void Draw();
