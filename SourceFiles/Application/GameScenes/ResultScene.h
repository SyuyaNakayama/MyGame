#pragma once
#include "BaseScene.h"
#include "Sprite.h"

// Œ‹‰Ê”­•\ƒV[ƒ“‚Ìˆ—
class ResultScene : public BaseScene
{
	std::unique_ptr<Sprite> sprite;

	void Initialize();
	void Update();
	void Draw();
};