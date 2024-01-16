#pragma once
#include "BaseScene.h"
#include "Stage.h"

class TutorialScene : public WristerEngine::BaseScene
{
	Stage stage;

	// BaseScene を介して継承されました
	void Initialize() override;
	void Update() override;
	// 終了
	void Finalize() { stage.Finalize(); }
};

class UIDrawerTutorialScene : public WristerEngine::_2D::AbstractUIDrawer
{
	std::unique_ptr<WristerEngine::_2D::Sprite> frame;
	std::map<WristerEngine::Key, std::unique_ptr<WristerEngine::_2D::Sprite>> keyUI;
	std::map<std::string, std::unique_ptr<WristerEngine::_2D::Sprite>> operateUI;

	// AbstractUIDrawer を介して継承されました
	void Initialize() override;
	void Update() override;
	void Draw() override;
};