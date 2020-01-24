/*****************************************************************************
template.h
CameraData.h
name	:新井 崚太
data	:2020/01/10 12:56:17
*****************************************************************************/
#ifndef CameraData_H
#define CameraData_H

//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include "object3D.h"

//////////////////////////////////////////////////////////////////////////////
//define定義
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//前方宣言
//////////////////////////////////////////////////////////////////////////////
class CModel;

//////////////////////////////////////////////////////////////////////////////
//CameraDataクラス
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

	void SetViewVector(XMVECTOR front, XMVECTOR right, XMVECTOR up) {
		_viewFront = front;
		_viewRight = right;
		_viewUp = up;
	}

	void SetQuaternion(XMVECTOR quaternion) { _quaternion = quaternion; }

	XMVECTOR GetFrontVector() { return _viewFront; }
	XMVECTOR GetRightVector() { return _viewRight; }
	XMVECTOR GetUpVector() { return _viewUp; }
	XMVECTOR GetQuaternion() { return _quaternion; }

	CModel* GetModel() { return _model; }

private:
	//XMFLOAT3 _position;

	XMVECTOR _viewFront;
	XMVECTOR _viewRight;
	XMVECTOR _viewUp;

	XMVECTOR _quaternion;
};

#endif // !CameraData_H

