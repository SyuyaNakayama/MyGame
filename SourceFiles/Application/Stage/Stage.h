#pragma once
#include "Player.h"
#include "Block.h"
#include "SpawnObject.h"
#include "JsonLoader.h"
#include <chrono>

class Stage
{
	std::vector<std::unique_ptr<Block>> blocks; // 壁と床
	Player player;
	std::list<std::unique_ptr<Object>> objects;
	std::list<std::unique_ptr<Goal>> goals;
	LevelData* levelData = nullptr;
	std::list<SpawnObject> spawnPoints;
	static int score;
	RealTimer stageTime;
	bool isFinished;
	
public:
	void Initialize();
	void Update();
	bool IsFinished() { return isFinished; }
	float GetRemainTime() { return stageTime.GetRemainTime(); }
	size_t GetObjectNum() { return objects.size(); }
	static void AddScore(int score_) { score += score_; }
	static void Reset() { score = 0; }
	static int GetScore() { return score; }
};