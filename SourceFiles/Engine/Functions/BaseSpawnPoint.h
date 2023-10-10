#pragma once
#include "Timer.h"

class BaseSpawnPoint
{
protected:
	FrameTimer spawnTimer;

public:
	virtual void Update() = 0;
};