#pragma once
#include "BaseScene.h"
#include "Stage.h"
#include "Object3d.h"
#include "AudioManager.h"

class GamePlayScene : public BaseScene
{
	Stage stage;
	ViewProjection viewProjection;
	Audio* audio = nullptr;

	void Initialize();
	void Update();
	void Draw();
};