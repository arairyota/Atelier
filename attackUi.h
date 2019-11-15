#pragma once
#include "actionUi.h"
class attackUi : public actionUi
{
public:
	attackUi() { actionUi(); };
	~attackUi() {};

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void Set(XMFLOAT2 position, XMFLOAT2 rotation, XMFLOAT2 scale, XMMATRIX mtx, CTexture* texture) override;
};