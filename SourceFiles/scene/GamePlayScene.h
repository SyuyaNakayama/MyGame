#pragma once
#include "BaseScene.h"
#include "Stage.h"
#include "JsonLoader.h"

class GamePlayScene : public BaseScene
{
	Stage stage;
	ViewProjection viewProjection;
	WorldTransform multiTexModelWT;

	void Initialize();
	void Update();
	void Draw();
};