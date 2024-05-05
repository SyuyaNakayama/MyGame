#include "PauseMenu.h"
#include "SceneManager.h"
using namespace WristerEngine::_2D;

PauseMenu* PauseMenu::GetInstance()
{
	static PauseMenu instance;
	return &instance;
}

void PauseMenu::Initialize()
{
	sprites["01_bg"] = Sprite::Create("UI/uiFrame.png", Half(WristerEngine::WIN_SIZE), { 0.5f,0.5f });
	sprites["01_bg"]->size = Const(Vector2, "BasePauseMenuFrameSize");

	std::vector<std::string> optionNames = { "Option","CameraSettings","Rot","Spd","Dis" };
	for (size_t i = 0; i < optionNames.size(); i++)
	{
		sprites[optionNames[i]] = Sprite::Create("UI/OptionText.png");
	}
	sprites["Option"]->Split({ 1,5 });
	sprites["CameraSettings"]->SetRect({ 160,32 }, { 0,32 });
	sprites["Rot"]->SetRect({ 64,32 }, { 0,64 });
	sprites["Spd"]->SetRect({ 64,32 }, { 96,64 });
	sprites["Dis"]->SetRect({ 64,32 }, { 0,96 });
	for (size_t i = 0; i < optionNames.size(); i++)
	{
		sprites[optionNames[i]]->size *= 2.0f;
		std::string str = optionNames[i] + "StringPos";
		sprites[optionNames[i]]->position = Const(Vector2, str);
	}

	items["CameraMode"] = std::make_unique<CameraModeItem>();
	for (auto& i : items) { i.second->Initialize(); }

	// �������ڏ����l
	param.moveSpd = items["CameraMode"]->GetParam();
}

void PauseMenu::Update()
{
	BasePauseMenu::Update();
	if (!isPause) { return; }
	// �|�[�Y���j���[����
	if (operateConfig->GetTrigger("Pause"))
	{
		WristerEngine::SceneManager::GetInstance()->Pause();
	}
	for (auto& i : items) { i.second->Update(); }

	// �������ڂ�n��
	param.moveSpd = items["CameraMode"]->GetParam();
}

void PauseMenu::Draw()
{
	WristerEngine::BasePauseMenu::Draw();
	for (auto& i : items) { i.second->Draw(); }
}

void BaseItem::Initialize()
{
	sprites["RightCursor"] = Sprite::Create("UI/SelectCursor.png", Const(Vector2, "RightCursor"));
	sprites["RightCursor"]->size = { 64,64 };
	sprites["LeftCursor"] = Sprite::Create("UI/SelectCursor.png", Const(Vector2, "LeftCursor"));
	sprites["LeftCursor"]->size = { 64,64 };
	sprites["LeftCursor"]->isFlipX = true;
}

void CameraModeItem::Initialize()
{
	BaseItem::Initialize();
	sprites["RotMode"] = Sprite::Create("UI/OptionText.png");
	sprites["RotMode"]->SetRect({ 64,32 }, { 0,128 });
	sprites["RotMode"]->size *= 2.0f;
	sprites["RotMode"]->position = Const(Vector2, "RotModeStringPos");

	param = -1.0f; // �����l
	animation.Initialize(Const(int, "CameraModeUiAnimationTime"), WristerEngine::Easing::Type::EaseOutQuint);
}

void CameraModeItem::SpriteMove()
{
	float easeVal = animation.Update();
	sprites["RotMode"]->textureLeftTop.x = ltMemX + easeVal * uiMoveDis;
	if (animation.IsFinish()) 
	{
		State = &CameraModeItem::Idle; 
		animation.Restart();
	}
}

void CameraModeItem::Idle()
{
	if (operateConfig->GetTrigger("Right"))
	{
		if (Half(Const(float, "CameraModeUiLTMoveDis")) < sprites["RotMode"]->textureLeftTop.x) { return; }
		IdleAction(Const(float, "CameraModeUiLTMoveDis"));
		param = 1.0f;
	}
	else if (operateConfig->GetTrigger("Left"))
	{
		if (Half(Const(float, "CameraModeUiLTMoveDis")) > sprites["RotMode"]->textureLeftTop.x) { return; }
		IdleAction(-Const(float, "CameraModeUiLTMoveDis"));
		param = -1.0f;
	}
}

void CameraModeItem::IdleAction(float uiMoveDis_)
{
	State = &CameraModeItem::SpriteMove;
	uiMoveDis = uiMoveDis_;
	ltMemX = sprites["RotMode"]->textureLeftTop.x;
}

void CameraModeItem::Update()
{
	(this->*State)();
	AbstractUIDrawer::Update();
}