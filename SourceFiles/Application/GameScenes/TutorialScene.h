#pragma once
#include "BaseScene.h"
#include "Stage.h"

class TutorialScene : public BaseScene
{
	Stage stage;

	// BaseScene ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	void Initialize() override;
	void Update() override;
	// I—¹
	void Finalize() { stage.Finalize(); }
};

class UIDrawerTutorialScene : public AbstractUIDrawer
{
	std::unique_ptr<Sprite> frame;
	std::map<Key, std::unique_ptr<Sprite>> keyUI;
	std::map<std::string, std::unique_ptr<Sprite>> operateUI;

	// AbstractUIDrawer ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	void Initialize() override;
	void Update() override;
	void Draw() override;
};