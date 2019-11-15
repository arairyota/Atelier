#pragma once
#include "scene.h"

class CAudioClip;

class TitleScene : public Scene
{
public:
	TitleScene();
	~TitleScene();

	void Init()override;
	void Uninit()override;
	void Update()override;
};

