#pragma once
#include "Block.h"
#include "JsonLoader.h"
#include "Player.h"
#include "SpawnObject.h"
#include <chrono>

// ステージに関係するオブジェクト全般のクラス
class Stage
{
	static const int STAGE_TIME = 60;

	std::list<std::unique_ptr<WristerEngine::_3D::GameObject>> gameObjects; // プレイヤー、壁、床、ゴール、障害物
	WristerEngine::LevelData* levelData = nullptr;
	static int score;
	WristerEngine::FrameTimer stageTime;
	bool isFinished;
	int fps = 0; // 取得したFPS

public:
	static float GROUND_POS_Y;

	// 初期化
	void Initialize();
	// 更新
	void Update();
	/// <summary>
	/// スコア加算(0未満にはならない)
	/// </summary>
	/// <param name="score_">加算するスコア</param>
	static void AddScore(int score_) { score = max(score + score_, 0); }
	// getter
	bool IsFinished() { return isFinished; }
	/// <summary>
	/// 残り時間を取得
	/// </summary>
	/// <returns>[0]に秒、[1]に999以下のミリ秒が入る</returns>
	std::array<int, 2> GetRemainTime();
	static int GetScore() { return score; }
	// スコアリセット
	static void ResetScore() { score = 0; }
	// タイムリセット
	void ResetTime() { stageTime = STAGE_TIME * fps; }
	// 終了
	void Finalize() { gameObjects.clear(); }
};