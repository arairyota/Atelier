#pragma once
#include "object2D.h"
#include "polygon.h"

class CPolygon;
//////////////////////////////////////////////////////////////////////////////
//攻撃、アイテム、スキルなんかに継承するクラス
//////////////////////////////////////////////////////////////////////////////
class actionUi : public CPolygon
{
protected:
	bool _is_select; //どのアクションが選択されたか管理するフラグ
	//CPolygon* _polygon;

public:
	actionUi() { _is_select = false; };
	~actionUi() {};

	virtual void Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Set(XMFLOAT2 position, XMFLOAT2 rotation, XMFLOAT2 scale, XMMATRIX mtx, CTexture* texture) override;
	void Translation(XMMATRIX mtx, XMFLOAT2 position) {
		_world = mtx;
		_position = position;
	};
};

/*
class attackUi : public actionUi {

};*/