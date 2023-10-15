#pragma once
#include "Timer.h"

// FPSä÷òAèàóù
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
	static FPS* GetInstance();
	void Initialize(float maxfps);
	// FPSå≈íË
	void Update();
	int GetFPS() { return fps; }
};