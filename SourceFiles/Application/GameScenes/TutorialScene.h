#pragma once
#include "BaseScene.h"
#include "Stage.h"

class TutorialScene : public BaseScene
{
	Stage stage;

	// BaseScene を介して継承されました
	void Initialize() override;
	void Update() override;
	// 終了
	void Finalize() { stage.Finalize(); }
};

class UIDrawerTutorialScene : public AbstractUIDrawer
{
	std::unique_ptr<Sprite> frame;
	std::map<Key, std::unique_ptr<Sprite>> keyUI;

	// AbstractUIDrawer を介して継承されました
	void Initialize() override;
	void Update() override;
	void Draw() override;
};