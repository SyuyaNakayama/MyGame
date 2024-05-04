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

	items.resize(1);
	items[0] = std::make_unique<CameraModeItem>();
	for (auto& i : items) { i->Initialize(); }
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
	for (auto& i : items) { i->Update(); }
}

void PauseMenu::Draw()
{
	WristerEngine::BasePauseMenu::Draw();
	for (auto& i : items) { i->Draw(); }
}

void BaseItem::Initialize()
{
	sprites["Cursor_01"] = Sprite::Create("UI/SelectCursor.png");
	sprites["Cursor_01"]->isFlipX = true;
	sprites["Cursor_01"]->position.x = 400.0f;
	sprites["Cursor_01"]->Update();
	//sprites["Cursor_02"] = Sprite::Create("UI/SelectCursor.png");
}

void CameraModeItem::Initialize()
{
	BaseItem::Initialize();
	sprites["RotMode"] = Sprite::Create("UI/OptionText.png");
	sprites["RotMode"]->SetRect({ 64,32 }, { 0,128 });
	sprites["RotMode"]->size *= 2.0f;
	sprites["RotMode"]->position = Const(Vector2, "RotModeStringPos");
}

void CameraModeItem::Update()
{
	AbstractUIDrawer::Update();
}