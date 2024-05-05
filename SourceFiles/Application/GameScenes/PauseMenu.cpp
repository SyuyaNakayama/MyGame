#include "PauseMenu.h"
#include "SceneManager.h"
#include <algorithm>
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

	sprites["RightCursor"] = Sprite::Create("UI/SelectCursor.png", Const(Vector2, "RightCursor"));
	sprites["RightCursor"]->size = { 64,64 };
	sprites["LeftCursor"] = Sprite::Create("UI/SelectCursor.png", Const(Vector2, "LeftCursor"));
	sprites["LeftCursor"]->size = { 64,64 };
	sprites["LeftCursor"]->isFlipX = true;

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

	items["Rot"] = std::make_unique<CameraModeItem>();
	items["Spd"] = std::make_unique<Spd_DisItem>();
	items["Dis"] = std::make_unique<Spd_DisItem>();
	for (auto& i : items)
	{
		i.second->SetPosY(sprites[i.first]->position.y);
		i.second->Initialize();
	}

	// UI��\��������
	for (auto& i : items) { i.second->Update(); }

	// �������ڏ����l
	param.moveSpd = items["Rot"]->GetParam();
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

	// �I�𒆂̍��ڂ����X�V����
	if (operateConfig->GetTrigger("Up")) { select--; }
	if (operateConfig->GetTrigger("Down")) { select++; }
	select = std::clamp(select, 0, (int)SELECT_STR.size() - 1);
	sprites["RightCursor"]->position.y = sprites[SELECT_STR[select]]->position.y;
	sprites["LeftCursor"]->position.y = sprites[SELECT_STR[select]]->position.y;
	items[SELECT_STR[select]]->Update();

	// �������ڂ�n��
	param.moveSpd = items["Rot"]->GetParam() * items["Spd"]->GetParam();
	param.dis = 20.0f * (items["Dis"]->GetParam() - 1.0f);
}

void PauseMenu::Draw()
{
	WristerEngine::BasePauseMenu::Draw();
	for (auto& i : items) { i.second->Draw(); }
}

void BaseItem::Initialize()
{
	animation.Initialize(Const(int, "ItemUiAnimationTime"), WristerEngine::Easing::Type::EaseOutQuint);
	for (auto& s : sprites) { s.second->position.y = posY; }
}

void BaseItem::Update()
{
	(this->*State)();
	AbstractUIDrawer::Update();
}

void BaseItem::IdleAction(float uiMoveDis_, const std::string& indexName)
{
	State = &BaseItem::SpriteMove;
	uiMoveDis = uiMoveDis_;
	ltMemX = sprites[indexName]->textureLeftTop.x;
}

void CameraModeItem::Initialize()
{
	sprites["RotMode"] = Sprite::Create("UI/OptionText.png");
	sprites["RotMode"]->SetRect({ 64,32 }, { 0,128 });
	sprites["RotMode"]->size *= 2.0f;
	sprites["RotMode"]->position = Const(Vector2, "RotModeStringPos");

	BaseItem::Initialize();

	param = -1.0f; // �����l
}

void CameraModeItem::SpriteMove()
{
	float easeVal = animation.Update();
	sprites["RotMode"]->textureLeftTop.x = ltMemX + easeVal * uiMoveDis;
	if (animation.IsFinish())
	{
		State = &BaseItem::Idle;
		animation.Restart();
	}
}

void Spd_DisItem::SpriteMove()
{
	float easeVal = animation.Update();
	sprites["Num"]->textureLeftTop.x = ltMemX + easeVal * uiMoveDis;
	if (animation.IsFinish())
	{
		State = &BaseItem::Idle;
		animation.Restart();
	}
}

void CameraModeItem::Idle()
{
	if (operateConfig->GetTrigger("Right"))
	{
		if (Half(Const(float, "CameraModeUiLTMoveDis")) < sprites["RotMode"]->textureLeftTop.x) { return; }
		IdleAction(Const(float, "CameraModeUiLTMoveDis"), "RotMode");
		param = 1.0f;
	}
	else if (operateConfig->GetTrigger("Left"))
	{
		if (Half(Const(float, "CameraModeUiLTMoveDis")) > sprites["RotMode"]->textureLeftTop.x) { return; }
		IdleAction(-Const(float, "CameraModeUiLTMoveDis"), "RotMode");
		param = -1.0f;
	}
}

void Spd_DisItem::Initialize()
{
	sprites["Num"] = Sprite::Create("UI/num.png", Const(Vector2, "SpdItemNumPos"));
	sprites["Num"]->SetRect({ 30,30 }, { 30 * paramVal,0 });
	sprites["Num"]->size = { 64,64 };
	sprites["Num"]->anchorPoint.x = 0.5f;

	BaseItem::Initialize();

	param = CalcParam(); // �����l
}

void Spd_DisItem::Idle()
{
	if (operateConfig->GetTrigger("Right"))
	{
		if (Const(float, "Spd_DisNumLTMoveDis") * 9.0f - 1.0f < sprites["Num"]->textureLeftTop.x) { return; }
		IdleAction(Const(float, "Spd_DisNumLTMoveDis"), "Num");
		paramVal++;
	}
	else if (operateConfig->GetTrigger("Left"))
	{
		if (Const(float, "Spd_DisNumLTMoveDis") + 1.0f > sprites["Num"]->textureLeftTop.x) { return; }
		IdleAction(-Const(float, "Spd_DisNumLTMoveDis"), "Num");
		paramVal--;
	}
	param = CalcParam();
}