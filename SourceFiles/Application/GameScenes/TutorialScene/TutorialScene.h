#pragma once
#include "BaseScene.h"
#include "PlayMode.h"
#include "TutorialEventManager.h"

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
	TutorialEventManager* eventManager = TutorialEventManager::GetInstance();

	// AbstractUIDrawer ����Čp������܂���
	void Initialize() override;
	void Update() override;
	void Draw() override;
};