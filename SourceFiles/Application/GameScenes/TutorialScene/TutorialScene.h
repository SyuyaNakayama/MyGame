#pragma once
#include "BaseScene.h"
#include "PlayMode.h"
#include "TutorialEvent.h"
#include "BasePauseMenu.h"

class TutorialScene : public WristerEngine::BaseScene
{
	Stage stage;

	// BaseScene ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	void Initialize() override;
	void Update() override;
	// I—¹
	void Finalize() { stage.Finalize(); }
};

class UIDrawerTutorialScene : public PlayMode
{
	TutorialEvent* tutorialEvent = TutorialEvent::GetInstance();
	std::map<WristerEngine::Key, std::unique_ptr<WristerEngine::_2D::Sprite>> keyUI;

	// AbstractUIDrawer ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	void Initialize() override;
	void Update() override;
	void Draw() override;
};