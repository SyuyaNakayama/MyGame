#include "Timer.h"
using namespace std::chrono;
#include <imgui.h>

bool FrameTimer::Update()
{
	if (--timer <= 0)
	{
		timer = timeMem;
		ImGui::Text("Hello,World!");
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
