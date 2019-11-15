#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "bullet.h"
#include "model.h"
#include "scene.h"
#include <vector>

void Bullet::Init()
{
	_position = XMFLOAT3{ 0.0f, 0.0f, 0.0f };
	_rotation = XMFLOAT3{ 0.0f, 0.0f, 0.0f };
	_scale = XMFLOAT3{ 0.0f, 0.0f, 0.0f };

	_front = XMVECTOR{0.0f, 0.0f, 1.0f};
	_right = XMVECTOR{ 1.0f, 0.0f, 0.0f };;
	_up = XMVECTOR{ 0.0f, 1.0f, 0.0f };;

	_model = new CModel;
	_model->Load("asset/miku_01.obj");
}

void Bullet::Uninit()
{
	_model->Unload();
}

void Bullet::Update()
{
	_position.x += XMVectorGetX(_front) * BULLET_SPEED;
	_position.y += XMVectorGetY(_front) * BULLET_SPEED;
	_position.z += XMVectorGetZ(_front) * BULLET_SPEED;

	_position.y = 10.0f;
	_life -= 1;

	if (_life < 0) {
		CManager::GetScene()->DestroyGameObject(this);
		return;
	}

	Enemy* enemy = CManager::GetScene()->GetGameObject<Enemy>(TYPE_ENEMY);
	std::vector<Enemy*>enemys;
	enemys = CManager::GetScene()->GetGameObjects<Enemy>(TYPE_ENEMY);

	if (enemy != nullptr) {
		for (Enemy* enemy : enemys) {
			XMFLOAT3 enemyPos = enemy->GetPosition();

			//衝突判定
			if (this->_position.x > enemyPos.x - 5.0f && this->_position.x < enemyPos.x + 5.0f &&
				this->_position.z > enemyPos.z - 5.0f && this->_position.z < enemyPos.z + 5.0f) {
				CManager::GetScene()->DestroyGameObject(enemy);
				CManager::GetScene()->DestroyGameObject(this);
				return;
			}
		}
	}
}

void Bullet::Draw()
{
	// マトリクス設定
	XMMATRIX world;
	world = XMMatrixScaling(_scale.x, _scale.y, _scale.z);
	world *= XMMatrixRotationRollPitchYaw(_rotation.x, _rotation.y, _rotation.z);
	world *= XMMatrixTranslation(_position.x, _position.y, _position.z);
	CRenderer::SetWorldMatrix(&world);

	_model->Draw();
}

void Bullet::Creat(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scale, XMVECTOR front, XMVECTOR right, XMVECTOR up, int life)
{
	_position = pos;
	_rotation = rot;
	_scale = scale;

	_front = front;
	_right = right;
	_up = up;

	_life = life;
}

//後で消す
void Bullet::Destroy()
{
	if (_life < 0) {
		//消す
	}
}