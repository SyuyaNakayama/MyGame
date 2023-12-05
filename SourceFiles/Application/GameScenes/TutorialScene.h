#pragma once
#include "BaseScene.h"
#include "Stage.h"

class TutorialScene : public BaseScene
{
	Stage stage;

	// BaseScene ����Čp������܂���
	void Initialize() override;
	void Update() override;
	// �I��
	void Finalize() { stage.Finalize(); }
};

class UIDrawerTutorialScene : public AbstractUIDrawer
{
	std::unique_ptr<Sprite> frame;
	std::map<Key, std::unique_ptr<Sprite>> keyUI;

	// AbstractUIDrawer ����Čp������܂���
	void Initialize() override;
	void Update() override;
	void Draw() override;
};