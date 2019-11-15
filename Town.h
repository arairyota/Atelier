#pragma once
#include "object3D.h"
class ModelLoader;
class Town : public object3D
{
private:
	ModelLoader* _modelA = NULL;
	ModelLoader* _modelB = NULL;

public:
	Town();
	~Town();

	void Init();
	void Uninit();
	void Update();
	void Draw();
	void Set(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scale);
};

