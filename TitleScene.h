#ifndef TitleScene_H
#define	TitleScene_H



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

#endif