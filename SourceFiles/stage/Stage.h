#pragma once
#include "Player.h"
#include "Block.h"
#include "Object.h"
#include "JsonLoader.h"

class Stage
{
	std::vector<std::unique_ptr<Block>> blocks; // ï«Ç∆è∞
	Player player;
	std::vector<std::unique_ptr<Object>> objects;
	LevelData* levelData = nullptr;
	
public:
	static const Vector2 STAGE_SIZE;
	void Initialize();
	void Update();
	void Draw();
};