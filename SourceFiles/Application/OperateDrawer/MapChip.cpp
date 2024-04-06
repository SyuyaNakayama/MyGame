#include "MapChip.h"
#include "Input.h"

using namespace WristerEngine::_2D;

void MapChip::VirtualInitialize(Sprite* sprite)
{
	sprite->textureSize.x /= 2.0f;
	sprite->size.x /= 2.0f;
}

void MapChip::Update()
{
	WristerEngine::Input* input = WristerEngine::Input::GetInstance();
	using Key = WristerEngine::Key;

	std::vector<std::vector<Key>> keys =
	{
		{Key::A},
		{Key::D},
		{Key::W},
		{Key::S},
		{Key::Left},
		{Key::Right},
		{Key::Up},
		{Key::Down},
		{Key::Lshift,Key::Rshift}
	};

	for (size_t i = 0; i < sprites.size(); i++)
	{
		// キーを押したらレクト位置を変える
		sprites[i]->textureLeftTop.x = input->IsAnyInput(keys[i]) * sprites[i]->textureSize.x;
		sprites[i]->Update();
	}
}
