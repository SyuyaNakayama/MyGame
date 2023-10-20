#include "FPS.h"
#include <thread>
using namespace std::chrono;

FPS* FPS::GetInstance()
{
	static FPS instance;
	return &instance;
}

void FPS::Initialize(float maxfps)
{
	reference = steady_clock::now();
	maxFPS = maxfps;
	oneSecond.Start();
}

void FPS::Fix()
{
	// 1/60秒ぴったりの時間
	const microseconds MIN_TIME(uint64_t(1000000.0f / maxFPS));
	// 1/60秒よりわずかに短い時間
	const microseconds MIN_CHECK_TIME(uint64_t(1000000.0f / (maxFPS + 5.0f)));

	// 現在時間を取得する
	steady_clock::time_point now = steady_clock::now();
	// 前回記録からの経過時間を取得する
	microseconds elapsed = duration_cast<microseconds>(now - reference);

	// 1/60秒(よりわずかに短い時間)経っていない場合
	if (elapsed < MIN_CHECK_TIME)
	{
		// 1/60秒経過するまで微小なスリープを繰り返す
		while (steady_clock::now() - reference < MIN_TIME)
		{
			// 1マイクロ秒スリープ
			std::this_thread::sleep_for(microseconds(1));
		}
	}

	oneSecondFrames.Update();
	if (oneSecond.Update())
	{
		fps = oneSecondFrames.GetTime();
		oneSecondFrames = INT32_MAX;
	}

	// 現在の時間を記録する
	reference = steady_clock::now();
}