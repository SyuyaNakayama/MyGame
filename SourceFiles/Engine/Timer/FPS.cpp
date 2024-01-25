#include "FPS.h"
#include <thread>
using namespace std::chrono;
using namespace WristerEngine;

FPS* FPS::GetInstance()
{
	static FPS instance;
	return &instance;
}

void FPS::Initialize()
{
	reference = steady_clock::now();
	oneSecond.Start();
}

void FPS::Fix()
{
	// �ʂ�ł������ϐ�
	const float MEGA = 1000000.0f;
	// 1/60�b�҂�����̎���
	const microseconds MIN_TIME(uint64_t(MEGA / MAX_FPS));
	// 1/60�b���킸���ɒZ������
	const float CHECK_TIME_OFFSET = 5;
	const microseconds MIN_CHECK_TIME(uint64_t(MEGA / (MAX_FPS + CHECK_TIME_OFFSET)));

	// ���ݎ��Ԃ��擾����
	steady_clock::time_point now = steady_clock::now();
	// �O��L�^����̌o�ߎ��Ԃ��擾����
	microseconds elapsed = duration_cast<microseconds>(now - reference);

	// 1/60�b(���킸���ɒZ������)�o���Ă��Ȃ��ꍇ
	if (elapsed < MIN_CHECK_TIME)
	{
		// 1/60�b�o�߂���܂Ŕ����ȃX���[�v���J��Ԃ�
		while (steady_clock::now() - reference < MIN_TIME)
		{
			// 1�}�C�N���b�X���[�v
			std::this_thread::sleep_for(microseconds(1));
		}
	}

	oneSecondFrames.Update();
	if (oneSecond.Update())
	{
		fps = oneSecondFrames.GetTime();
		oneSecondFrames = INT32_MAX;
	}

	// ���݂̎��Ԃ��L�^����
	reference = steady_clock::now();
}