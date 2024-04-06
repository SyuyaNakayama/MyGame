#pragma once
#include "BaseScene.h"
#include "PlayMode.h"
#include "TutorialEvent.h"

class TutorialScene : public WristerEngine::BaseScene
{
	Stage stage;

	// BaseScene を介して継承されました
	void Initialize() override;
	void Update() override;
	// 終了
	void Finalize() { stage.Finalize(); }
};

class UIDrawerTutorialScene : public PlayMode
{
	TutorialEvent* tutorialEvent = TutorialEvent::GetInstance();
	std::map<WristerEngine::Key, std::unique_ptr<WristerEngine::_2D::Sprite>> keyUI;

	// AbstractUIDrawer を介して継承されました
	void Initialize() override;
	void Update() override;
	void Draw() override;
};