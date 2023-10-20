#include "Timer.h"
using namespace std::chrono;

std::array<int, 2> FrameTimer::ConvertToSecond(int time, int fps) const
{
	std::array<float, 2> timef{};
	// �~���b���擾���邽�߂̕ϐ�
	const float KILO = 1000.0f;
	// �c�莞�Ԃ��擾
	float t = (float)time / fps;
	// �������Ə������𕪗�
	timef[1] = modf(t, &timef[0]);
	return std::array<int, 2>({ (int)timef[0], (int)(timef[1] * KILO) });
}

bool FrameTimer::Update()
{
	if (++timer >= timeMem)
	{
		timer = 0;
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

float RealTimer::GetTime() const
{
	return (float)duration_cast<milliseconds>(nowTime - startTime).count() / 1000.0f;
}
