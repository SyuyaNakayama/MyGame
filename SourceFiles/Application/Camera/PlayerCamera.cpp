#include "PlayerCamera.h"
#include "Input.h"
#include "SceneManager.h"
#include <algorithm>
using namespace WristerEngine::_2D;
using namespace WristerEngine::_3D;

void PlayerCamera::Initialize(Transform* parent)
{
	BaseCamera::Initialize(parent);
	CameraShake::Prop shakeProp = { {0,0,0},10,WristerEngine::Easing::Type::Sqrt };
	viewProjection.Initialize(&shakeProp);
	const float INIT_DISTANCE = 30.0f;
	distance = INIT_DISTANCE;
	parentPrePos = parent->GetWorldPosition();
}

void PlayerCamera::Update()
{
	Vector2 cameraMove;
	const float MOVE_SPD = 1.0f;

	WristerEngine::Input* input = WristerEngine::Input::GetInstance();
	if (!input->IsConnectGamePad())
	{
		cameraMove.x = input->Move(WristerEngine::Key::Left, WristerEngine::Key::Right, MOVE_SPD);
		cameraMove.y = input->Move(WristerEngine::Key::Up, WristerEngine::Key::Down, MOVE_SPD);
	}
	else
	{
		cameraMove = input->ConRStick(1.0f);
	}

	angle += cameraMove / rotSpdDec;
	const Angle Y_MAX = 72;
	angle.y = std::clamp(angle.y, (float)Angle(5), +Y_MAX);
	BaseCamera::Update();
	parentPrePos = worldTransform.parent->GetWorldPosition();
	if (input->IsTrigger(WristerEngine::Key::_3)) { ModelManager::SetViewProjection(&viewProjection); }
}