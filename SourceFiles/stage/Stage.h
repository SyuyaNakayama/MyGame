#pragma once
#include "Player.h"
#include "Block.h"
#include "SpawnObject.h"
#include "JsonLoader.h"

class Stage
{
	std::vector<std::unique_ptr<Block>> blocks; // ï«Ç∆è∞
	Player player;
	std::list<std::unique_ptr<Object>> objects;
	std::list<std::unique_ptr<Goal>> goals;
	LevelData* levelData = nullptr;
	std::list<SpawnObject> spawnPoints;
	static int score;
	
public:
	void Initialize();
	void Update();
	static void AddScore(int score) { Stage::score += score; }
	static void Reset() { score = 0; }
	static int GetScore() { return score; }
};