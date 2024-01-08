#include "PlayerCamera.h"
#include "Input.h"
#include "SceneManager.h"
#include <algorithm>

void PlayerCamera::Initialize(WorldTransform* parent)
{
	BaseCamera::Initialize(parent);
	const float INIT_DISTANCE = 30.0f;
	distance = INIT_DISTANCE;
	parentPrePos = parent->GetWorldPosition();
}

void PlayerCamera::Update()
{
	Vector2 cameraMove;
	const float MOVE_SPD = 1.0f;
	
	Input* input = Input::GetInstance();
	if (!input->IsConnectGamePad())
	{
		cameraMove.x = Input::GetInstance()->Move(Key::Left, Key::Right, MOVE_SPD);
		cameraMove.y = Input::GetInstance()->Move(Key::Up, Key::Down, MOVE_SPD);
	}
	else
	{
		cameraMove = Input::GetInstance()->ConRStick(1.0f);
	}

	angle += cameraMove / rotSpdDec;
	const Angle Y_MAX = 72;
	angle.y = std::clamp(angle.y, 0.0f, +Y_MAX);
	BaseCamera::Update();
	parentPrePos = worldTransform.parent->GetWorldPosition();
	if (input->IsTrigger(Key::_3)) { ModelManager::SetViewProjection(&viewProjection); }
}