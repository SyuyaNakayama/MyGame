#pragma once
#include "Timer.h"

// スポーンオブジェクト基底クラス
class BaseSpawnPoint
{
protected:
	FrameTimer spawnTimer;

public:
	virtual void Update() = 0;
};