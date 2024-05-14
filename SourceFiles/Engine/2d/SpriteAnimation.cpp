#include "SpriteAnimation.h"
using namespace WristerEngine;
using namespace _2D;

void SpriteAnimation::Initialize(const std::string& textureName, size_t spriteWidth, int animationIntervel)
{
	sprite = Sprite::Create(textureName);
	width = spriteWidth;
	interval = animationIntervel;
	animeNumMax = (size_t)sprite->size.x / width;
	sprite->size = { (float)width,sprite->size.y };
	sprite->textureSize = { (float)width,sprite->textureSize.y };
	sprite->Update();
}

void SpriteAnimation::Update()
{
	if (sprite->isInvisible) { return; }
	if (interval.Update())
	{
		if (++animeNum >= animeNumMax) { animeNum = 0; }
		sprite->textureLeftTop = { (float)animeNum * width ,0 };
	}
	sprite->Update();
}