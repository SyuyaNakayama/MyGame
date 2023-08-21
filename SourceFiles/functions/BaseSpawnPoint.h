#pragma once
#include "Timer.h"

class BaseSpawnPoint
{
protected:
	FrameTimer spawnTimer;

public:
	virtual void Spawn() = 0;
};