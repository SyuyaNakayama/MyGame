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
}
