#ifndef RESULTSCENE_H
#define RESULTSCENE_H

#include "scene.h"

class ResultScene : public Scene
{
public:
	ResultScene();
	~ResultScene();

	void Init();
	void Uninit();
	void Update();
};

#endif // !RESULTSCENE_H