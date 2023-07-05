#include "Player.h"
#include "Input.h"
#include <imgui.h>

void Player::Initialize()
{
	model = Model::Create("player", true);
	worldTransform.Initialize();
	worldTransform.translation = { 0,5.0f,-20.0f };
	camera = std::make_unique<PlayerCamera>();
	Model::SetViewProjection(camera->GetViewProjection());
	camera->Initialize(&worldTransform);
	physics = Physics::Create(&worldTransform);
	collisionAttribute = CollisionAttribute::Player;
	collisionMask = CollisionMask::Player;
}

void Player::Move()
{
	Input* input = Input::GetInstance();

	std::vector<Key> keys = { Key::D,Key::A,Key::W,Key::S };
	if (input->IsAnyInput(keys))
	{
		physics->SetForce(0.15f);
		Vector3 forcedir;
		forcedir.x = input->IsInput(Key::D) - input->IsInput(Key::A);
		forcedir.z = input->IsInput(Key::W) - input->IsInput(Key::S);
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
	model->Draw(worldTransform);
}