#include "Easing.h"
#include "MathUtility.h"

using namespace WristerEngine;

const float Easing::MAX = 1.0f;

float(Easing::* Easing::Ease[])() =
{
	&Easing::Sqrt,
	&Easing::OutElastic,
	&Easing::OutBounce,
};

float Easing::OutElastic()
{
	const float c4 = (2.0f * PI) / 3.0f;

	if (x == 0) { return 0; }
	return powf(2.0f, -10.0f * x) * sinf((x * 10.0f - 0.75f) * c4) + 1.0f;
}

float Easing::OutBounce()
{
	const float n1 = 7.5625f;
	const float d1 = 2.75f;

	if (x < 1 / d1) { return n1 * x * x; }
	else if (x < 2.0f / d1) { return n1 * (x -= 1.5f / d1) * x + 0.75f; }
	else if (x < 2.5f / d1) { return n1 * (x -= 2.25f / d1) * x + 0.9375f; }
	else { return n1 * (x -= 2.625f / d1) * x + 0.984375f; }
}

void Easing::Initialize(int easeTime, Type type_)
{
	timer = easeTime;
	type = type_;
}

float Easing::Update()
{
	if (isFinish) { return Easing::MAX; }
	x = timer.GetTimeRate();
	float easeNum = (this->*Ease[(int)type])();
	isFinish = timer.Update();
	return easeNum;
}
