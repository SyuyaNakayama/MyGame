#pragma once
#include "BaseScene.h"
#include "Stage.h"
#include "JsonLoader.h"
#include "Object3d.h"

class GamePlayScene : public BaseScene
{
	Stage stage;
	ViewProjection viewProjection;
	std::unique_ptr<Object3d> object;

	void Initialize();
	void Update();
	void Draw();
};