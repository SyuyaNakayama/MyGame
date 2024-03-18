#pragma once
#include "Timer.h"

namespace WristerEngine
{
	// �X�|�[���I�u�W�F�N�g���N���X
	class AbstractSpawnPoint
	{
	protected:
		FrameTimer spawnTimer;

	public:
		// ���z�f�X�g���N�^
		virtual ~AbstractSpawnPoint() = default;
		// �X�V
		virtual void Update() = 0;
	};
}