#pragma once
#include "BaseScene.h"

class PauseMenu
{
	bool isPause = false;

public:
	void Initialize();
	void Update();
	void Draw();
	void Pause() { isPause = !isPause; }
	bool IsPause() const { return isPause; }
};