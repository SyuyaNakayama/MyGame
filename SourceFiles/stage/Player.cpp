#include "Player.h"
#include "Input.h"

void Player::Initialize()
{
	model = Model::Create("player", true);
	worldTransform.Initialize();
	worldTransform.translation.y = 5.0f;
	camera = std::make_unique<PlayerCamera>();
	Model::SetViewProjection(camera->GetViewProjection());
	camera->Initialize(&worldTransform);
}

void Player::Move()
{
	Input* input = Input::GetInstance();

	std::vector<Key> keys = { Key::D,Key::A,Key::W,Key::S };
	if (input->IsAnyInput(keys))
	{
		force = 0.15f;
		forceDir.x = input->IsInput(Key::D) - input->IsInput(Key::A);
		forceDir.z = input->IsInput(Key::W) - input->IsInput(Key::S);
		forceDir *= Matrix4::RotateY(camera->GetAngle().x);
	}
	else { force = 0; }
}

void Player::Update()
{
	Move();
	camera->Update();
	Physics::Update();
	worldTransform.Update();
}

void Player::Draw()
{
	model->Draw(worldTransform);
}
