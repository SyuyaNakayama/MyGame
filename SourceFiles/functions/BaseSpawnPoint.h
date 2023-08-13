#pragma once
#include "Timer.h"

class BaseSpawnPoint
{
protected:
	Timer spawnTimer;

public:
	virtual void Spawn() = 0;
};