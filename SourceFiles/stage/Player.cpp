#include "Player.h"
#include "Input.h"
#include <imgui.h>

void Player::Initialize(const ObjectData& objectData)
{
	object = ModelManager::Create("player", true);
	worldTransform = &object->worldTransform;
	worldTransform->translation = objectData.translation;
	camera = std::make_unique<PlayerCamera>();
	ModelManager::SetViewProjection(camera->GetViewProjection());
	camera->Initialize(worldTransform);
	physics = Physics::Create(worldTransform);
	collisionAttribute = CollisionAttribute::Player;
	collisionMask = CollisionMask::Player;
	physics->SetMu(0.22f);
}

void Player::Move()
{
	Input* input = Input::GetInstance();

	std::vector<Key> keys = { Key::D,Key::A,Key::W,Key::S };
	if (input->IsAnyInput(keys))
	{
		physics->SetForce(0.15f);
		Vector3 forcedir;
		forcedir.x = (float)(input->IsInput(Key::D) - input->IsInput(Key::A));
		forcedir.z = (float)(input->IsInput(Key::W) - input->IsInput(Key::S));
		forcedir *= Matrix4::RotateY(camera->GetAngle().x);
		physics->SetForceDir(forcedir);
	}
	else { physics->SetForce(0); }
}

void Player::Update()
{
	Move();
	camera->Update();
	physics->Update();
}

void Player::Draw()
{
	object->Draw();
}