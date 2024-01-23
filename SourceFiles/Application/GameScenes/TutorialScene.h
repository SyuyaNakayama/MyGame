#pragma once
#include "BaseScene.h"
#include "Stage.h"
#include "OperateDrawer.h"

class TutorialScene : public WristerEngine::BaseScene
{
	Stage stage;

	// BaseScene ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	void Initialize() override;
	void Update() override;
	// I—¹
	void Finalize() { stage.Finalize(); }
};

class UIDrawerTutorialScene : public OperateDrawer
{

	// AbstractUIDrawer ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	void Initialize() override;
	void Update() override;
	void Draw() override;
};