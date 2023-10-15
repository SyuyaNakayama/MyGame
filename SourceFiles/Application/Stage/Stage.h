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
	// 初期化
	void Initialize();
	// 更新
	void Update();
	/// <summary>
	/// スコア加算
	/// </summary>
	/// <param name="score_">加算するスコア</param>
	static void AddScore(int score_) { score += score_; }
	// getter
	bool IsFinished() { return isFinished; }
	float GetRemainTime() { return stageTime.GetRemainTime(); }
	static int GetScore() { return score; }
	// スコアリセット
	static void ResetScore() { score = 0; }
	// タイムリセット
	void ResetTime() { stageTime = STAGE_TIME; }
};