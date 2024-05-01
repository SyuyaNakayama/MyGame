#pragma once
#include "BaseScene.h"
#include "PlayMode.h"
#include "TutorialEvent.h"
#include "BasePauseMenu.h"

class TutorialScene : public WristerEngine::BaseScene
{
	Stage stage;

	// BaseScene ����Čp������܂���
	void Initialize() override;
	void Update() override;
	// �I��
	void Finalize() { stage.Finalize(); }
};

class UIDrawerTutorialScene : public PlayMode
{
	TutorialEvent* tutorialEvent = TutorialEvent::GetInstance();
	std::map<WristerEngine::Key, std::unique_ptr<WristerEngine::_2D::Sprite>> keyUI;

	// AbstractUIDrawer ����Čp������܂���
	void Initialize() override;
	void Update() override;
	void Draw() override;
};