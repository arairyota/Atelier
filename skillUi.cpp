#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "texture.h"
#include "actionUi.h"
#include "skillUi.h"
#include "scene.h"
#include "Flag.h"

skillUi::skillUi()
{
	actionUi::actionUi();
}


skillUi::~skillUi()
{
}

void skillUi::Init()
{
	actionUi::Init();
}

void skillUi::Uninit()
{
	actionUi::Uninit();
}

void skillUi::Update()
{
	actionUi::Update();
	if (Flag::GetGamePhase() == FLAG_SKILL_SELECT) {
		if (CInput::GetKeyTrigger('E')) {
			Flag::SetGamePhase(FLAG_TARGET_SELECT);
			Scene* scene = CManager::GetScene();
			TargetSelect* target = scene->AddGameObject<TargetSelect>(TYPE_OBJECT);
			target->Set(FLAG_SKILL_SELECT);
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

void skillUi::Draw()
{
	if (Flag::GetGamePhase() == FLAG_ACTION_SELECT) {
		actionUi::Draw();
	}
}

void skillUi::Set(XMFLOAT2 position, XMFLOAT2 rotation, XMFLOAT2 scale, XMMATRIX mtx, CTexture* texture)
{
	actionUi::Set(position, rotation, scale, mtx, texture);
}
