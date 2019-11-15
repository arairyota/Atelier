#pragma once
#include "actionUi.h"
class skillUi :
	public actionUi
{
public:
	skillUi();
	~skillUi();

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void Set(XMFLOAT2 position, XMFLOAT2 rotation, XMFLOAT2 scale, XMMATRIX mtx, CTexture* texture) override;

};

