#pragma once
#include "BaseScene.h"
#include "Stage.h"
#include "JsonLoader.h"

class GamePlayScene : public BaseScene
{
	Stage stage;
	ViewProjection viewProjection;
	Quaternion rotQ;
	Angle rotAngle = 0;
	std::unique_ptr<Model> multiTexModel;
	WorldTransform multiTexModelWT;

	void Initialize();
	void Update();
	void Draw();
};