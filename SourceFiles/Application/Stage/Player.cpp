#include "Player.h"
#include "Input.h"
#include "SceneManager.h"
#include "Stage.h"
#include <imgui.h>

const float Player::PLAYER_MOVE_FORCE = 0.15f;

void Player::Initialize(const ObjectData& objectData)
{
	object = ModelManager::Create("player", true);
	object->worldTransform.reset(objectData.worldTransform);
	worldTransform = object->worldTransform.get();
	camera = std::make_unique<PlayerCamera>();
	ModelManager::SetViewProjection(camera->GetViewProjection());
	camera->Initialize(object->worldTransform.get());
	physics = Physics::Create(worldTransform);
	collisionAttribute = CollisionAttribute::Player;
	collisionMask = CollisionMask::Player;
	physics->SetMu(0.23f);
	physics->SetVelocity({});
	physics->SetForce(0);
	if (SceneManager::GetInstance()->GetNowScene() == Scene::Play ||
		SceneManager::GetInstance()->GetNowScene() == Scene::Tutorial)
	{
		Move = &Player::Move_Play;
	}
}

void Player::Move_Play()
{
	Input* input = Input::GetInstance();

	std::vector<Key> keys = { Key::D,Key::A,Key::W,Key::S };
	if (input->IsAnyInput(keys))
	{
		physics->SetForce(PLAYER_MOVE_FORCE);
		Vector3 forcedir;
		forcedir.x = (float)(input->IsInput(Key::D) - input->IsInput(Key::A));
		forcedir.z = (float)(input->IsInput(Key::W) - input->IsInput(Key::S));
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
	else if (SceneManager::GetInstance()->GetNowScene() == Scene::Title)
	{
		if (moveTimer.Update()) { Move = &Player::Move_Title; }
	}
	physics->Update();
	camera->Update();
}