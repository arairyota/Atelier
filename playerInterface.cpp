#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "input.h"
#include "GameObject.h"
#include "attackUi.h"
#include "itemUi.h"
#include "skillUi.h"
#include "playerInterface.h"
#include "Flag.h"
#include "scene.h"

void playerInterface::Init()
{
	Scene* scene = CManager::GetScene();
	_position = XMFLOAT2(0.0f, 0.0f);
	_rotation = XMFLOAT2(0.0f, 0.0f);
	_scale    = XMFLOAT2(1.0f, 1.0f);

	_attackUi = scene->AddGameObject<attackUi>(TYPE_WIDGET);
	_itemUi = scene->AddGameObject<itemUi>(TYPE_WIDGET);
	_skillUi = scene->AddGameObject<skillUi>(TYPE_WIDGET);

	_world = XMMatrixIdentity();

	_world *= XMMatrixScaling(_scale.x, _scale.y, 0.0f);
	_world *= XMMatrixTranslation(_position.x, _position.y, 0.0f);
	//world *= XMMatrixRotationRollPitchYaw(_rotation.x, _rotation.y, _rotation.z);
	_world *= XMMatrixRotationY(_rotation.y);

	_uiPos = 0.0f;
	_selectType = FLAG_ATTACK_SELECT;
	_isActionPhase = true;

	//Flag::SetGamePhase(FLAG_ACTION_SELECT);
	_attackUi->Set(XMFLOAT2(0.0f, 0.0f + _uiPos), XMFLOAT2(0.0f, 0.0f) , XMFLOAT2(1.0f, 1.0f), _world, TextureManager::GetInstance()->GetTexture(ATTACK));
	_itemUi->Set(XMFLOAT2(0.0f, -200.0f + _uiPos), XMFLOAT2(0.0f, 0.0f), XMFLOAT2(1.0f, 1.0f), _world, TextureManager::GetInstance()->GetTexture(ITEM));
	_skillUi->Set(XMFLOAT2(0.0f, 200.0f + _uiPos), XMFLOAT2(0.0f, 0.0f), XMFLOAT2(1.0f, 1.0f), _world, TextureManager::GetInstance()->GetTexture(SKILL));
}

void playerInterface::Uninit()
{

}

void playerInterface::Update()
{
	if (Flag::GetGamePhase() == FLAG_ACTION_SELECT) {
		if (_isFirst) {
			//Flag::SetGamePhase(FLAG_ACTION_SELECT);
			//Flag::SetSelectAction(FLAG_ACTION_SELECT);
			Scene* scene = CManager::GetScene();
			CCamera* camera = scene->GetGameObject<CCamera>(TYPE_CAMERA);
			camera->Init();
			_isFirst = false;
		}
		_world = XMMatrixIdentity();

		_world *= XMMatrixScaling(_scale.x, _scale.y, 0.0f);
		_world *= XMMatrixTranslation(_position.x, _position.y, 0.0f);
		//world *= XMMatrixRotationRollPitchYaw(_rotation.x, _rotation.y, _rotation.z);
		_world *= XMMatrixRotationY(_rotation.y);

		//CRenderer::SetWorldViewProjection2D(_position, _rotation, _scale, _world);

		//Ç»ÇÒÇ©ëÄçÏÇ∑ÇÈ
		if (_selectType < FLAG_SKILL_SELECT) {
			if (CInput::GetKeyTrigger('W')) {
				_uiPos -= _move;
				_selectType = _selectType << 1;

			}
		}

		if (_selectType > FLAG_ITEM_SELECT) {
			if (CInput::GetKeyTrigger('S')) {
				_uiPos += _move;
				_selectType = _selectType >> 1;
			}
		}

		if (CInput::GetKeyTrigger('E')) {
			Flag::SetGamePhase(_selectType ); //ëIëÇ≥ÇÍÇΩèàóùÇ…ÉtÉâÉOÇóßÇƒÇÈ
			Flag::SetSelectAction(_selectType);

		}

		_attackUi->SetDrawFlag(true);
		_itemUi->SetDrawFlag(true);
		_skillUi->SetDrawFlag(true);

		_attackUi->Translation(_world, XMFLOAT2(0.0f, 0.0f + _uiPos));
		_itemUi->Translation(_world, XMFLOAT2(0.0f, -200.0f + _uiPos));
		_skillUi->Translation(_world, XMFLOAT2(0.0f, 200.0f + _uiPos));
		
		//_attackUi->Set(XMFLOAT2(0.0f, 0.0f + _uiPos), XMFLOAT2(0.0f, 0.0f), XMFLOAT2(15.0f, 10.0f), _world, ATTACK); //å„Ç≈textureSetä÷êîçÏÇÈ
		//_itemUi->Set(XMFLOAT2(0.0f, -200.0f + _uiPos), XMFLOAT2(0.0f, 0.0f), XMFLOAT2(15.0f, 10.0f), _world, ITEM);
		//_skillUi->Set(XMFLOAT2(0.0f, 200.0f + _uiPos), XMFLOAT2(0.0f, 0.0f), XMFLOAT2(15.0f, 10.0f), _world, SKILL);
	}
	else {
		_isFirst = true;
	}
}
 
void playerInterface::Set()
{
	_position = XMFLOAT2(200.0f, 500.0f);
	_rotation = XMFLOAT2(0.0f, 0.0f);
	_scale = XMFLOAT2(1.0f, 1.0f);
	
}
