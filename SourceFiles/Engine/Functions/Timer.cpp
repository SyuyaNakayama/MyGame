#include "Timer.h"
using namespace std::chrono;

bool FrameTimer::Update()
{
	if (--timer <= 0)
	{
		timer = timeMem;
		return true;
	}
	return false;
}

bool RealTimer::Update()
{
	nowTime = steady_clock::now();
	if (GetTime() >= timeMem)
	{
		startTime = nowTime;
		return true;
	}
	return false;
}

float RealTimer::GetTime()
{
	return (float)duration_cast<milliseconds>(nowTime - startTime).count() / 1000.0f;
}
