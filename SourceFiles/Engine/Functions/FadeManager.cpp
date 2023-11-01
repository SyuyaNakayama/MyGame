#include "FadeManager.h"
#include "WindowsAPI.h"

void FadeManager::Initialize()
{
	sprite = Sprite::Create("white1x1.png");
	sprite->size = WindowsAPI::GetInstance()->WIN_SIZE;
}

void FadeManager::Update()
{
	const float ALPHA_MAX = 1.0f;
	
	if (!isFade) { return; }
	isChange = false;
	alpha += fadePerFlame;
	if (alpha >= ALPHA_MAX)
	{
		alpha = ALPHA_MAX;
		fadePerFlame = -fadePerFlame;
		isChange = true;
	}
	if (alpha <= 0)
	{
		alpha = 0;
		fadePerFlame = -fadePerFlame;
		isFade = false;
	}
	sprite->color.a = alpha;
	sprite->Update();
}