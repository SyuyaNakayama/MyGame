#include "PlayerCamera.h"
#include "Input.h"
#include "SceneManager.h"
#include <algorithm>

void PlayerCamera::Initialize(WorldTransform* parent)
{
	BaseCamera::Initialize(parent);
	distance = 25.0f;
	parentPrePos = parent->GetWorldPosition();
}

void PlayerCamera::Update()
{
	Vector2 cameraMove;
	
	Input* input = Input::GetInstance();
	if (!input->IsConnectGamePad())
	{
		cameraMove.x = Input::GetInstance()->Move(Key::Left, Key::Right, 1.0f);
		cameraMove.y = Input::GetInstance()->Move(Key::Up, Key::Down, 1.0f);
	}
	else
	{
		cameraMove = Input::GetInstance()->ConRStick(1.0f);
	}

	angle += cameraMove / 25.0f;
	angle.y = std::clamp(angle.y, -PI / 2.5f, PI / 2.5f);
	BaseCamera::Update();
	parentPrePos = worldTransform.parent->GetWorldPosition();
}
