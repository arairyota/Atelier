/*****************************************************************************
CamearEditor.h
CamearEditor.h
name	:�V�� �Ñ�
data	:2019/12/27 15:48:37
*****************************************************************************/
#ifndef CamearEditor_H
#define CamearEditor_H

//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include <list>
#include "CameraData.h"

//////////////////////////////////////////////////////////////////////////////
//define��`
//////////////////////////////////////////////////////////////////////////////

//�\����
struct SelectData
{
	CameraData* _data = nullptr;
	std::list<CameraData*>::iterator _it;
	bool _isDelete = false;
};

//////////////////////////////////////////////////////////////////////////////
//�O���錾
//////////////////////////////////////////////////////////////////////////////
class CCamera;
class CameraData;

//////////////////////////////////////////////////////////////////////////////
//CamearEditor�N���X
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
	SelectData* _selectData; //����������邽�߂Ɏd���Ȃ�������ϐ�
	int _radio = 0;

	void DefaultCameraDataInit();	//�f�t�H���g�J�����f�[�^������

	bool _isEnable = true;

	char _fileName[64] = "";

	//std::vector<CameraData> _listv;
	CameraData _listv[100];


	//�v���C�x�[�g�֐�
	void EditorModeMenu();
	void EditorMenu();
	void FileMenu();
	void OperationMenu();
	void PresetMenu();
	void ReservationErase(); //�����\��

protected:

};

#endif // !CamearEditor_H

//void Init();
//void Uninit();
//void Update();
//void Draw();
