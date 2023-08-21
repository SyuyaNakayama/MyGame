#pragma once
#include "BaseScene.h"
#include "Sprite.h"

class ResultScene : public BaseScene
{
	std::unique_ptr<Sprite> sprite;

	void Initialize();
	void Update();
	void Draw();
};