#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "GameObject.h"
#include "gameActor.h"
#include "camera.h"
#include "Mesh.h"
#include "MeshCylinder.h"
#include "MeshField.h"
#include "MeshWall.h"
#include "model.h"
#include "polygon.h"
#include "player.h"
#include "enemy.h"
#include "billboard.h"
#include "ModelLoader.h"
#include "Town.h"
#include "playerInterface.h"
#include "TargetSelect.h"
#include "BattleJudg.h"
#include "ActionPhase.h"
#include "scene.h"

void Scene::Uninit()
{
	for (int cnt = 0; cnt < TYPE_LIST_MAX; cnt++) {
		for (GameObject* object : _GameObject[cnt]) {
			object->Uninit();
			delete object;
		}
		_GameObject[cnt].clear();
	}
}

void Scene::Update()
{
	for (int cnt = 0; cnt < TYPE_LIST_MAX; cnt++) {
		for (GameObject* object : _GameObject[cnt]) {
			
			if( !object->GetDestroy()) object->Update();	//消すフラグが立ってなかったら更新
		}
		_GameObject[cnt]._Remove_if([](GameObject* object) {
			return object->Destroy(); }); //[]名前のない関数(の引数){の処理}
	}
}

void Scene::Draw()
{
	for (int cnt = 0; cnt < TYPE_LIST_MAX; cnt++) {
		for (GameObject* object : _GameObject[cnt]) {
			object->Draw();
		}
	}
}
