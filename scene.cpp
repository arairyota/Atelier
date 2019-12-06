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
			object->Update();
		}
		_GameObject[cnt]._Remove_if([](GameObject* object) {
			return object->Destroy(); }); //[]–¼‘O‚Ì‚È‚¢ŠÖ”(‚Ìˆø”){‚Ìˆ—}
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
