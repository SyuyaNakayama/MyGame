#pragma once
#include "BaseScene.h"
#include "Stage.h"
#include "Object3d.h"

class GamePlayScene : public BaseScene
{
	Stage stage;
	ViewProjection viewProjection;
	std::unique_ptr<Sprite> ui;

	void Initialize();
	void Update();
	void Draw();
};