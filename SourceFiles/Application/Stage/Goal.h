#pragma once
#include "Collider.h"
#include "GameObject.h"
#include "Random.h"
#include "TutorialEvent.h"

enum class Score
{
	_M10 = -10,
	_10 = 10,
	_20 = 20,
	_30 = 30,
	_50 = 50,
};

class Goal;

// ゴールの共通部分を管理
class GoalManager final
{
private:
	Scene nowScene = Scene::Null;
	WristerEngine::Constant* constant = WristerEngine::Constant::GetInstance();
	WristerEngine::FrameTimer scoreChangeTimer = 600;
	bool isScoreChange = false;
	WristerEngine::Roulette roulette;
	TutorialEvent* tutorialEvent = TutorialEvent::GetInstance();
	const std::vector<UINT32>* tutorialEventPhase = nullptr;
	UINT32 phase = 0;
	std::vector<Goal*> goals;
	WristerEngine::LoopEasing goalColor;
	bool preTutorialEnd = false; // 前フレームのチュートリアル終了フラグ

	GoalManager() = default;
	~GoalManager() = default;
	// チュートリアルではないかを取得
	bool IsNotTutorial() const { return nowScene != Scene::Tutorial || tutorialEvent->IsEnd(); }

public:
	std::map<Score, std::string> SCORE_TEX_NAME =
	{
		{ Score::_M10,"Textures/score-10.png" },
		{ Score::_10, "Textures/score10.png" },
		{ Score::_20, "Textures/score20.png" },
		{ Score::_30, "Textures/score30.png" },
		{ Score::_50, "Textures/score50.png" }
	};
	
	GoalManager(const GoalManager& obj) = delete;
	GoalManager& operator=(const GoalManager& obj) = delete;

	// インスタンス取得
	static GoalManager* GetInstance();
	// 初期化
	void Initialize();
	// 更新
	void Update();

	/// <summary>
	/// スコアを取得
	/// </summary>
	/// <returns>次のスコア</returns>
	Score GetScore() const;

	// チュートリアルの説明を進める
	void NextPhase() { tutorialEvent->NextPhase(); }
	// ゴールオブジェクトのポインタを追加
	void AddGoalPointer(Goal* pGoal) { goals.push_back(pGoal); }
	// ゴールオブジェクトのポインタを消す
	void ResetGoalPointer() { goals.clear(); }
};

// ゴールのオブジェクト
class Goal : public WristerEngine::BoxCollider, public WristerEngine::_3D::GameObject
{
	friend GoalManager;

	GoalManager* manager = GoalManager::GetInstance();
	WristerEngine::_3D::Object3d* object = nullptr;
	Vector3 normal;
	Score score = Score::_10;
	WristerEngine::ColorRGBA initColor;

	/// <summary>
	/// スコア変更処理
	/// </summary>
	/// <param name="nextScore">次のスコア</param>
	void ChangeScore(Score nextScore);

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="objectData">Jsonファイルから読み込んだデータ</param>
	void Initialize(const ObjectData& objectData);
	// 更新
	void Update(){}
	// 衝突コールバック関数(BoxCollider版)
	void OnCollision(BoxCollider* collider);

	/// <summary>
	/// 色を変える
	/// </summary>
	/// <param name="colorRate">明度</param>
	void ChangeColor(float colorRate);
};