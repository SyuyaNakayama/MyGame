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

	// UIを表示させる
	for (auto& i : items) { i.second->Update(); }

	// 調整項目初期値
	param.moveSpd = items["Rot"]->GetParam();
}

void PauseMenu::Update()
{
	BasePauseMenu::Update();
	if (!isPause) { return; }
	// ポーズメニュー解除
	if (operateConfig->GetTrigger("Pause"))
	{
		WristerEngine::SceneManager::GetInstance()->Pause();
	}

	// 選択中の項目だけ更新する
	if (operateConfig->GetTrigger("Up")) { select--; }
	if (operateConfig->GetTrigger("Down")) { select++; }
	select = std::clamp(select, 0, (int)SELECT_STR.size() - 1);
	sprites["RightCursor"]->position.y = sprites[SELECT_STR[select]]->position.y;
	sprites["LeftCursor"]->position.y = sprites[SELECT_STR[select]]->position.y;
	items[SELECT_STR[select]]->Update();

	// 調整項目を渡す
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

void BaseItem::IdleAction(float uiMoveDis_)
{
	State = &BaseItem::SpriteMove;
	uiMoveDis = uiMoveDis_;
	ltMemX = sprites[spriteIndexName]->textureLeftTop.x;
}

void CameraModeItem::Initialize()
{
	spriteIndexName = "RotMode";
	sprites[spriteIndexName] = Sprite::Create("UI/OptionText.png");
	sprites[spriteIndexName]->SetRect({ 64,32 }, { 0,128 });
	sprites[spriteIndexName]->size *= 2.0f;
	sprites[spriteIndexName]->position = Const(Vector2, "RotModeStringPos");

	BaseItem::Initialize();

	param = -1.0f; // 初期値
}

void BaseItem::SpriteMove()
{
	float easeVal = animation.Update();
	sprites[spriteIndexName]->textureLeftTop.x = ltMemX + easeVal * uiMoveDis;
	if (animation.IsFinish())
	{
		State = &BaseItem::Idle;
		animation.Restart();
	}
}

void CameraModeItem::Idle()
{
	if (operateConfig->GetPush("Right"))
	{
		if (Half(Const(float, "CameraModeUiLTMoveDis")) < sprites[spriteIndexName]->textureLeftTop.x) { return; }
		IdleAction(Const(float, "CameraModeUiLTMoveDis"));
		param = 1.0f;
	}
	else if (operateConfig->GetPush("Left"))
	{
		if (Half(Const(float, "CameraModeUiLTMoveDis")) > sprites[spriteIndexName]->textureLeftTop.x) { return; }
		IdleAction(-Const(float, "CameraModeUiLTMoveDis"));
		param = -1.0f;
	}
}

void Spd_DisItem::Initialize()
{
	spriteIndexName = "Num";
	sprites[spriteIndexName] = Sprite::Create("UI/num.png", Const(Vector2, "SpdItemNumPos"));
	sprites[spriteIndexName]->SetRect({ 30,30 }, { 30 * paramVal,0 });
	sprites[spriteIndexName]->size = { 64,64 };
	sprites[spriteIndexName]->anchorPoint.x = 0.5f;

	BaseItem::Initialize();

	param = CalcParam(); // 初期値
}

void Spd_DisItem::Idle()
{
	if (operateConfig->GetPush("Right"))
	{
		if (Const(float, "Spd_DisNumLTMoveDis") * 9.0f - 1.0f < sprites[spriteIndexName]->textureLeftTop.x) { return; }
		IdleAction(Const(float, "Spd_DisNumLTMoveDis"));
		paramVal++;
	}
	else if (operateConfig->GetPush("Left"))
	{
		if (Const(float, "Spd_DisNumLTMoveDis") + 1.0f > sprites[spriteIndexName]->textureLeftTop.x) { return; }
		IdleAction(-Const(float, "Spd_DisNumLTMoveDis"));
		paramVal--;
	}
	param = CalcParam();
}