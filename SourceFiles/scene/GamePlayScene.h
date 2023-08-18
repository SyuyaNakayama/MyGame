#pragma once
#include "BaseScene.h"
#include "Stage.h"
#include "Object3d.h"
#include "FontManager.h"

class GamePlayScene : public BaseScene
{
	Stage stage;
	ViewProjection viewProjection;
	FontManager fm;
	unsigned char* image;

	void Initialize();
	void Update();
	void Draw();
};