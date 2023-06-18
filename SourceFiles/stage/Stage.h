#pragma once
#include "Player.h"
#include "Block.h"
#include "Object.h"

class Stage
{
	std::array<Block, 5> blocks; // ï«Ç∆è∞
	Player player;
	std::vector<std::unique_ptr<Object>> objects;
	void SetBlocks();

public:
	static const Vector2 STAGE_SIZE;
	void Initialize();
	void Update();
	void Draw();
};