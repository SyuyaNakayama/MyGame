#pragma once
#include "BaseScene.h"
#include "Stage.h"
#include "OperateDrawer.h"

class TutorialScene : public WristerEngine::BaseScene
{
	Stage stage;

	// BaseScene ����Čp������܂���
	void Initialize() override;
	void Update() override;
	// �I��
	void Finalize() { stage.Finalize(); }
};

class UIDrawerTutorialScene : public OperateDrawer
{

	// AbstractUIDrawer ����Čp������܂���
	void Initialize() override;
	void Update() override;
	void Draw() override;
};