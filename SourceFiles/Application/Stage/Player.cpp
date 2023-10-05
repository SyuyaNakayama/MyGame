#include "Player.h"
#include "Input.h"
#include "SceneManager.h"
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
	if (SceneManager::GetInstance()->GetNowScene() == Scene::Play) { Move = &Player::Move_Play; }
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
	worldTransform->translation.y = 5;
}

void Player::Move_Title()
{
	physics->SetForce(PLAYER_MOVE_FORCE);
	bool mt = moveTimer.Update();
	isTurn = NumberLoop(isTurn + mt, 2);
	if (isTurn == 0) { physics->SetForceDir(Vector3::MakeAxis(Axis::Z)); if (mt) moveTimer = 70; }
	if (isTurn == 1) { physics->SetForce(0); if (mt)moveTimer = 50; }
	if (isTurn == 2) { physics->SetForceDir(-Vector3::MakeAxis(Axis::Z)); if (mt)moveTimer = 60; }
}

void Player::Update()
{
	if (Move) { (this->*Move)(); }
	else if (SceneManager::GetInstance()->GetNowScene() == Scene::Title)
	{
		if (moveTimer.Update()) { moveTimer = 80; Move = &Player::Move_Title; }
	}
	physics->Update();
	camera->Update();
}