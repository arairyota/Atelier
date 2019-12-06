#ifndef GameScene_H
#define GameScene_H



#include "scene.h"



class CAudioClip;

class GameScene : public Scene
{
private:
	CAudioClip* _bgm;

public:
	GameScene();
	~GameScene();

	void Init();
	void Uninit();
	void Update();

};

#endif // !GameScene_H