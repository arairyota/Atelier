#pragma once
#include "scene.h"


const CHARACTER_STATS puni = CHARACTER_STATS(100.0f, 1.0f, 100.0f, 30.0f, 30.0f, 10.0f);
const CHARACTER_STATS araisan = CHARACTER_STATS(300.0f, 300.0f, 300.0f, 50.0f, 25.0f, 20.0f);

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

