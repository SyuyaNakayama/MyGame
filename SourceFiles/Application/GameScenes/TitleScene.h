#pragma once
#include "BaseScene.h"
#include "SpriteAnimation.h"
#include "Stage.h"

class TitleScene : public BaseScene
{
	std::unique_ptr<Sprite> ui;
	Stage stage;
	ViewProjection camera;
	SpriteAnimation spaceKeyUI;

	void Initialize();
	void Update();
	void Draw();
};