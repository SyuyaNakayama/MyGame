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

// ゴールの共通部分を管理
class GoalManager final
{
private:
	WristerEngine::FrameTimer scoreChangeTimer = 600;
	bool isScoreChange = false;
	WristerEngine::Roulette roulette;
	TutorialEvent* tutorialEvent = TutorialEvent::GetInstance();
	const std::vector<UINT32>* tutorialEventPhase = nullptr;
	UINT32 phase = 0;

	GoalManager() = default;
	~GoalManager() = default;

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

	/// <summary>
	/// isScoreChangeを取得
	/// </summary>
	/// <returns>isScoreChange</returns>
	bool IsScoreChange() const { return isScoreChange; }

	int GetChangeRemainTime() const { return scoreChangeTimer.GetRemainTime(); }

	UINT32 GetPhase() const { return phase; }
	const std::vector<UINT32>* GetTutorialEventPhase() const { return tutorialEventPhase; }

	bool IsTutorialEnd() const { return tutorialEvent->IsEnd(); }

	void NextPhase() { tutorialEvent->NextPhase(); }
};

// ゴールのオブジェクト
class Goal : public WristerEngine::BoxCollider, public WristerEngine::_3D::GameObject
{
	GoalManager* manager = GoalManager::GetInstance();
	WristerEngine::_3D::Object3d* object = nullptr;
	Vector3 normal;
	Score score = Score::_10;
	WristerEngine::ColorRGBA initColor;

	// スコア変更処理
	void ChangeScore();

public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="objectData">Jsonファイルから読み込んだデータ</param>
	void Initialize(const ObjectData& objectData);
	// 更新
	void Update();
	// 衝突コールバック関数(BoxCollider版)
	void OnCollision(BoxCollider* collider);
};