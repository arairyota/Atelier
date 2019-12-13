#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "actionUi.h"
#include "Flag.h"
#include "camera.h"
#include "TargetSelect.h"

#include "scene.h"
#include "attackUi.h"

void attackUi::Init()
{
	actionUi::Init();
}

void attackUi::Uninit()
{
	actionUi::Uninit();
}

void attackUi::Update()
{
	actionUi::Update();

	if (Flag::GetGamePhase() == FLAG_ATTACK_SELECT) {
		if (CInput::GetKeyTrigger('E')) {
			Flag::SetGamePhase(FLAG_TARGET_SELECT);
			Scene* scene = CManager::GetScene();
			TargetSelect* target = scene->AddGameObject<TargetSelect>(TYPE_OBJECT);
			target->Set(FLAG_ATTACK_SELECT);
			

		}

		if (CInput::GetKeyTrigger('Q')) {
			Flag::SetGamePhase(FLAG_ACTION_SELECT);
			Flag::SetSelectAction(FLAG_ACTION_SELECT);
			Scene* scene = CManager::GetScene();
			CCamera* camera = scene->GetGameObject<CCamera>(TYPE_CAMERA);
			camera->Init();
		}		
	}
}

void attackUi::Draw()
{
	if (Flag::GetGamePhase() == FLAG_ACTION_SELECT) {
		actionUi::Draw();
	}
}

void attackUi::Set(XMFLOAT2 position, XMFLOAT2 rotation, XMFLOAT2 scale, XMMATRIX mtx, CTexture* texture)
{
	actionUi::Set(position,rotation, scale, mtx, texture);
}
