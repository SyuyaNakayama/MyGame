#pragma once
#include "BaseScene.h"
#include "Stage.h"
#include "Object3d.h"
#include "FontManager.h"

class GamePlayScene : public BaseScene
{
	Stage stage;
	ViewProjection viewProjection;
	FontManager font;

	void Initialize();
	void Update();
	void Draw();
};