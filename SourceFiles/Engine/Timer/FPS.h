#pragma once
#include "Timer.h"

// FPS�֘A����
class FPS
{
private:
	std::chrono::steady_clock::time_point reference;
	float maxFPS = 0;
	int fps = 0;
	RealTimer oneSecond = 1.0f;
	FrameTimer oneSecondFrames = INT32_MAX;

	FPS() = default;
	~FPS() = default;

public:
	// �C���X�^���X�擾
	static FPS* GetInstance();
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="maxfps">�ő�FPS�l</param>
	void Initialize(float maxfps);
	// FPS�Œ�
	void Fix();
	// FPS�擾
	int GetFPS() { return fps; }
};