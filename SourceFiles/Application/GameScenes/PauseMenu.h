#pragma once
#include "BaseScene.h"

class PauseMenu : public WristerEngine::BaseScene
{
	// BaseScene を介して継承されました
	void Initialize() override;
	void Update() override;
};