#pragma once
#include "BaseScene.h"
#include "Sprite.h"

class TitleScene : public BaseScene
{
	std::unique_ptr<Sprite> ui;
	void Initialize();
	void Update();
	void Draw();
};