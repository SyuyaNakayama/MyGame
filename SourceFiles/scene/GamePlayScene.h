#pragma once
#include "BaseScene.h"
#include "Stage.h"
#include "JsonLoader.h"

class GamePlayScene : public BaseScene
{
	Stage stage;

	void Initialize();
	void Update();
	void Draw();
};