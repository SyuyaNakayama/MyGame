#pragma once
#include "BaseScene.h"
#include "Sprite.h"
#include "Stage.h"

class TitleScene : public BaseScene
{
	std::unique_ptr<Sprite> ui;
	Stage stage;
	void Initialize();
	void Update();
	void Draw();
};