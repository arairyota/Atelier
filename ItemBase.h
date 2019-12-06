/*****************************************************************************
ItemBase.h
ItemBase.h
name	:�V�� �Ñ�
data	:2019/08/12 12:21:33
*****************************************************************************/
#ifndef ItemBase_H
#define ItemBase_H

//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "object3D.h"
#include "polygon.h"

//////////////////////////////////////////////////////////////////////////////
//define��`
//////////////////////////////////////////////////////////////////////////////
#define ITEM_TYPE_ATTACK	(0x01)
#define ITEM_TYPE_HEEL		(0x02)


//////////////////////////////////////////////////////////////////////////////
//�O���錾
//////////////////////////////////////////////////////////////////////////////
class CTexture;
class Billboard;


//////////////////////////////////////////////////////////////////////////////
//ItemBase�N���X
//////////////////////////////////////////////////////////////////////////////
class ItemBase : public object3D {
private:
	XMFLOAT2 position2D;

public:
	ItemBase() {
		_scale = XMFLOAT3(2.0f, 2.0f, 2.0f);
	};

	CTexture* GetTexture() {
		return _Texture;
	}

	CPolygon* GetPolygon() {
		return _polygon;
	}

	void SetPolygon(CPolygon* polygon) {
		_polygon = polygon;
	}

	void SetPosition2D(float x, float y) {
		position2D = XMFLOAT2(x, y);
		
	}

	virtual void Use(XMFLOAT3 position)=0;	//�A�C�e���g�p
protected:
	
	int _num;	//������
	CPolygon* _polygon; //2D�|���S��
	Billboard* _billboard;
};

#endif // !ItemBase_H

//void Init();
//void Uninit();
//void Update();
//void Draw();
