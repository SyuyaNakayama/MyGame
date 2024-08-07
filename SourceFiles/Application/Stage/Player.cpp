#include "Player.h"
#include "Stage.h"
#include "OperateConfig.h"
#include <imgui.h>

using namespace WristerEngine::_3D;

void Player::Initialize(const ObjectData& objectData)
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
	if (GetNowScene() == Scene::Play || GetNowScene() == Scene::Tutorial)
	{
		Move = &Player::Move_Play;
	}
}

void Player::Move_Play()
{
	OperateConfig* operateConfig = OperateConfig::GetInstance();

	using Key = WristerEngine::Key;
	std::vector<Key> keys = { Key::D,Key::A,Key::W,Key::S };
	//if (input->IsConnectGamePad())
	//{

	//}
	//else if (input->IsAnyInput(keys))
	//{
	//	float force = GetMoveForce();
	//	if (operateConfig->GetPush("Dash")) { force *= 2.0f; }
	//	physics->SetForce(force);
	//	Vector3 forcedir;
	//	forcedir.x = input->Move(Key::D, Key::A, 1.0f);
	//	forcedir.z = input->Move(Key::W, Key::S, 1.0f);
	//	forcedir *= Matrix4::RotateY(camera->GetAngle().x);
	//	physics->SetForceDir(forcedir);
	//}
	//else { physics->SetForce(0); }
	float force = GetMoveForce();
	if (operateConfig->GetPush("Dash")) { force *= 2.0f; }
	physics->SetForce(force);
	Vector3 forcedir;
	forcedir.x = input->Move(Key::D, Key::A, 1.0f);
	forcedir.z = input->Move(Key::W, Key::S, 1.0f);
	if (input->IsConnectGamePad())
	{
		Vector2 conDir = input->ConLStick(1.0f);
		forcedir = { conDir.x,0,conDir.y };
	}
	forcedir *= Matrix4::RotateY(camera->GetAngle().x);
	physics->SetForceDir(forcedir);

	if (input->IsTrigger(Key::R))
	{
		worldTransform->translation = {};
	}

	worldTransform->translation.y = Stage::GROUND_POS_Y;
}

void Player::Move_Title()
{
	physics->SetForce(GetMoveForce());
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
	else if (GetNowScene() == Scene::Title)
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