#include "PlayerCamera.h"
#include "Input.h"
#include "SceneManager.h"
#include <algorithm>
#include "PauseMenu.h"
#include "Constant.h"
using namespace WristerEngine::_2D;
using namespace WristerEngine::_3D;

void PlayerCamera::Initialize(Transform* parent)
{
	BaseCamera::Initialize(parent);
	CameraShake::Prop shakeProp = { {0,0,0},10,WristerEngine::Easing::Type::Sqrt };
	viewProjection.Initialize(&shakeProp);
}

void PlayerCamera::Update()
{
	const PauseMenu* pauseMenu = PauseMenu::GetInstance();
	Vector2 cameraMove;
	CameraParam param = pauseMenu->GetCameraParam();
	const float MOVE_SPD = param.moveSpd / rotSpdDec;
	distance = WEConst(float, "PlayerCameraInitDis") + param.dis;

	WristerEngine::Input* input = WristerEngine::Input::GetInstance();
	if (!input->IsConnectGamePad())
	{
		cameraMove.x = input->Move(WristerEngine::Key::Right, WristerEngine::Key::Left, MOVE_SPD);
	}
	else
	{
		cameraMove.x = input->ConRStick(MOVE_SPD).x;
	}

	angle += cameraMove;
	BaseCamera::Update();
}