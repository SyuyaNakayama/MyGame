#pragma once
#include "Timer.h"

// スポーンオブジェクト基底クラス
class BaseSpawnPoint
{
protected:
	FrameTimer spawnTimer;

public:
	// 更新
	virtual void Update() = 0;
};