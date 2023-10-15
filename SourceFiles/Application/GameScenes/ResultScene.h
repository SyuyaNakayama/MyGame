#pragma once
#include "BaseScene.h"
#include "Sprite.h"

// 結果発表シーンの処理
class ResultScene : public BaseScene
{
	std::unique_ptr<Sprite> sprite;

	void Initialize();
	void Update();
	void Draw();
};