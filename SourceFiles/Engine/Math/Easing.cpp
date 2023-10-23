#include "Easing.h"

float(Easing::* Easing::Ease[])() =
{
	&Easing::Sqrt,
};

void Easing::Initialize(int easeTime, Type type_)
{
	easeRate = easeTime;
	type = type_;
}

float Easing::Update()
{
	if (isFinish) { return 1.0f; }
	float easeNum = (this->*Ease[(int)type])();
	isFinish = easeRate.Update();
	return easeNum;
}
