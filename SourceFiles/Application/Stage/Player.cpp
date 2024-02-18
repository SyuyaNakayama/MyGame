#include "Player.h"
#include "Input.h"
#include "SceneManager.h"
#include "Stage.h"
#include <imgui.h>

using namespace WristerEngine::_3D;

const float Player::PLAYER_MOVE_FORCE = 0.15f;

void Player::Initialize(const WristerEngine::ObjectData& objectData)
{
	object = ModelManager::Create("player", true);
	object->worldTransform.reset(objectData.worldTransform);
	worldTransform = object->worldTransform.get();
	camera = std::make_unique<PlayerCamera>();
	ModelManager::SetViewProjection(camera->GetViewProjection());
	camera->Initialize(object->worldTransform.get());
	physics = WristerEngine::Physics::Create(worldTransform);
	collisionAttribute = CollisionAttribute::Player;
	collisionMask = CollisionMask::Player;
	physics->SetMu(0.23f);
	physics->SetVelocity({});
	physics->SetForce(0);
	if (WristerEngine::SceneManager::GetInstance()->GetNowScene() == Scene::Play ||
		WristerEngine::SceneManager::GetInstance()->GetNowScene() == Scene::Tutorial)
	{
		Move = &Player::Move_Play;
	}
}

void Player::Move_Play()
{
	WristerEngine::Input* input = WristerEngine::Input::GetInstance();

	std::vector<WristerEngine::Key> keys = { WristerEngine::Key::D,WristerEngine::Key::A,WristerEngine::Key::W,WristerEngine::Key::S };
	if (input->IsAnyInput(keys))
	{
		physics->SetForce(PLAYER_MOVE_FORCE);
		Vector3 forcedir;
		forcedir.x = (float)(input->IsInput(WristerEngine::Key::D) - input->IsInput(WristerEngine::Key::A));
		forcedir.z = (float)(input->IsInput(WristerEngine::Key::W) - input->IsInput(WristerEngine::Key::S));
		forcedir *= Matrix4::RotateY(camera->GetAngle().x);
		physics->SetForceDir(forcedir);
	}
	else { physics->SetForce(0); }
	worldTransform->translation.y = Stage::GROUND_POS_Y;
}

void Player::Move_Title()
{
	physics->SetForce(PLAYER_MOVE_FORCE);
	const float PLAYER_MAX_Z = 50.0f;

	if (isTurn == 0)
	{
		if (worldTransform->translation.z <= PLAYER_MAX_Z) { physics->SetForceDir(Vector3::MakeAxis(Axis::Z)); }
		else { physics->SetForceDir(-Vector3::MakeAxis(Axis::Z)); isTurn = 1; }
	}
	if (isTurn != 1) { return; }
	if (worldTransform->translation.z <= 0)
	{
		if (Object::GetInstanceNum() != 0)
		{
			physics->SetForceDir(Vector3::MakeAxis(Axis::Z)); isTurn = 0;
		}
		else { physics->SetForce(0); }
	}
}

void Player::Update()
{
	if (Move) { (this->*Move)(); }
	else if (WristerEngine::SceneManager::GetInstance()->GetNowScene() == Scene::Title)
	{
		if (moveTimer.Update()) { Move = &Player::Move_Title; }
	}
	physics->Update();
	camera->Update();
}

void Player::OnCollision(SphereCollider* collider)
{
	// 相手がObjectかの判定をする
	Object* obj = dynamic_cast<Object*>(collider);
	if (!obj) { return; }

	float spd = physics->GetVelocity().Length();
	camera->GetViewProjection()->shake->SetShakeRange({ spd,spd,spd });
	// Objectと当たったならシェイク
	camera->StartShake();
}