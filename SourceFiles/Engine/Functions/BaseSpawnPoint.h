#pragma once
#include "Timer.h"

// �X�|�[���I�u�W�F�N�g���N���X
class BaseSpawnPoint
{
protected:
	FrameTimer spawnTimer;

public:
	virtual void Update() = 0;
};