#pragma once
#include "Player.h"
#include "Block.h"
#include "SpawnObject.h"
#include "JsonLoader.h"
#include <chrono>

// ステージに関係するオブジェクト全般のクラス
class Stage
{
	static float STAGE_TIME;

	std::list<std::unique_ptr<GameObject>> gameObjects; // プレイヤー、壁、床、ゴール、障害物
	LevelData* levelData = nullptr;
	static int score;
	RealTimer stageTime;
	bool isFinished;
	
public:
	void Initialize();
	void Update();
	bool IsFinished() { return isFinished; }
	float GetRemainTime() { return stageTime.GetRemainTime(); }
	static void AddScore(int score_) { score += score_; }
	static void ResetScore() { score = 0; }
	void ResetTime() { stageTime = STAGE_TIME; }
	static int GetScore() { return score; }
};