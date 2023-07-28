#pragma once
#include "BaseScene.h"
#include "Stage.h"
#include "Object3d.h"

class GamePlayScene : public BaseScene
{
	Stage stage;
	ViewProjection viewProjection;

	void Initialize();
	void Update();
	void Draw();
};