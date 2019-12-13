/*****************************************************************************
DamegeNumEffect.h
DamegeNumEffect.h
name	:�V�� �Ñ�
data	:2019/08/03 14:15:54
*****************************************************************************/
#ifndef DamegeNumEffect_H
#define DamegeNumEffect_H

//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "billboard.h"

//////////////////////////////////////////////////////////////////////////////
//define��`
//////////////////////////////////////////////////////////////////////////////
#define LIFE_SPAN (120)

//////////////////////////////////////////////////////////////////////////////
//�O���錾
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//DamegeNumEffect�N���X
//////////////////////////////////////////////////////////////////////////////
class DamegeNumEffect : public Billboard{
private:
	unsigned short _beginFrame;
	unsigned short _nowFrame;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void Set(XMFLOAT3 position, int damegeNum, float transX);

protected:

};

#endif // !DamegeNumEffect_H

//void Init();
//void Uninit();
//void Update();
//void Draw();