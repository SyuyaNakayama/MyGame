#pragma once
#include <chrono>

// フレーム単位でのタイマー
class FrameTimer
{
private:
	int timer;
	int timeMem;

public:
	FrameTimer(int timer_ = 0) { timer = timeMem = timer_; }
	bool Update();
	int GetTime() { return timer; }
	float GetTimeRate() { return (float)timer / (float)timeMem; }
	int GetRemainTime() { return timeMem - timer; }
	float GetRemainTimeRate() { return (float)GetRemainTime() / (float)timeMem; }
	int GetInterval() { return timeMem; }
};

// 現実時間でのタイマー
class RealTimer
{
private:
	std::chrono::steady_clock::time_point startTime;
	std::chrono::steady_clock::time_point nowTime;
	float timeMem;

public:
	RealTimer(float limitTime = 0) { timeMem = limitTime; startTime = std::chrono::steady_clock::now(); }
	bool Update();
	void Start(){ startTime = std::chrono::steady_clock::now(); }
	float GetTime();
	float GetTimeRate() { return GetTime() / timeMem; }
	float GetRemainTime() { return timeMem - GetTime(); }
	float GetRemainTimeRate() { return GetRemainTime() / timeMem; }
	float GetInterval() { return timeMem; }
};
