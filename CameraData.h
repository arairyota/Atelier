/*****************************************************************************
template.h
CameraData.h
name	:�V�� �Ñ�
data	:2020/01/10 12:56:17
*****************************************************************************/
#ifndef CameraData_H
#define CameraData_H

//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "object3D.h"

//////////////////////////////////////////////////////////////////////////////
//define��`
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//�O���錾
//////////////////////////////////////////////////////////////////////////////
class CModel;

//////////////////////////////////////////////////////////////////////////////
//CameraData�N���X
//////////////////////////////////////////////////////////////////////////////
class CameraData : public object3D{
public:
	CameraData();
	void Init();
	void Uninit();
	void Update();
	void Draw();
	//void Set();

	XMFLOAT3 GetPosition();

	float* GetPositionX() { return &_position.x; };
	float* GetPositionY() { return &_position.y; };
	float* GetPositionZ() { return &_position.z; };

	void SetPosition(float x, float y, float z) {
		_position = XMFLOAT3(x, y, z);
	};

	void SetPosition(XMFLOAT3 pos) {
		_position = pos;
	}

	CModel* GetModel() { return _model; }

private:
	//XMFLOAT3 _position;

	XMVECTOR _viewFront;
	XMVECTOR _viewRight;
	XMVECTOR _viewUp;
};

#endif // !CameraData_H

