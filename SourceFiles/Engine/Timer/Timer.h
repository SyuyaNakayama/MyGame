#pragma once
#include <chrono>

// �t���[���P�ʂł̃^�C�}�[
class FrameTimer
{
private:
	int timer;
	int timeMem;

public:
	// �R���X�g���N�^
	FrameTimer(int timer_ = 0) { timer = timeMem = timer_; }
	// �X�V
	bool Update();
	// getter
	int GetTime() { return timer; }
	float GetTimeRate() { return (float)timer / (float)timeMem; }
	int GetRemainTime() { return timeMem - timer; }
	float GetRemainTimeRate() { return (float)GetRemainTime() / (float)timeMem; }
	int GetInterval() { return timeMem; }
};

// �������Ԃł̃^�C�}�[
class RealTimer
{
private:
	std::chrono::steady_clock::time_point startTime;
	std::chrono::steady_clock::time_point nowTime;
	float timeMem;

public:
	// �R���X�g���N�^
	RealTimer(float limitTime = 0) { timeMem = limitTime; startTime = std::chrono::steady_clock::now(); }
	// �X�V
	bool Update();
	// �v���J�n
	void Start(){ startTime = std::chrono::steady_clock::now(); }
	// getter
	float GetTime();
	float GetTimeRate() { return GetTime() / timeMem; }
	float GetRemainTime() { return timeMem - GetTime(); }
	float GetRemainTimeRate() { return GetRemainTime() / timeMem; }
	float GetInterval() { return timeMem; }
};
