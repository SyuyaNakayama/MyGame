#pragma once
#include "Timer.h"

namespace WristerEngine
{
	// �X�|�[���I�u�W�F�N�g���N���X
	class BaseSpawnPoint
	{
	protected:
		FrameTimer spawnTimer;

	public:
		// �X�V
		virtual void Update() = 0;
	};
}