#pragma once
#include "Collider.h"
#include "GameObject.h"
#include "Random.h"
#include "TutorialEvent.h"

// 床と壁のオブジェクト
class Block : public WristerEngine::BoxCollider, public WristerEngine::_3D::GameObject
{
	WristerEngine::_3D::Object3d* object = nullptr;
	Vector3 normal;

public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="objectData">Jsonファイルから読み込んだデータ</param>
	void Initialize(const ObjectData& objectData);
	// 更新
	void Update() {}
	// 衝突コールバック関数(BoxCollider版)
	void OnCollision(BoxCollider* collider);
};

// ゴールのオブジェクト
class Goal : public WristerEngine::BoxCollider, public WristerEngine::_3D::GameObject
{
	enum class Score
	{
		_M10 = -10,
		_10 = 10,
		_20 = 20,
		_30 = 30,
		_50 = 50,
	};

	static std::map<Score, std::string> SCORE_TEX_NAME;
	static const std::vector<Score> SCORE_TABLE;
	static WristerEngine::FrameTimer scoreChangeTimer;
	static bool isScoreChange;
	static WristerEngine::Random_Int randScore;
	static WristerEngine::Roulette roulette;
	static TutorialEvent* tutorialEvent;
	static const std::vector<UINT32>* tutorialEventPhase;
	static UINT32 phase;

	WristerEngine::_3D::Object3d* object = nullptr;
	Vector3 normal;
	Score score = Score::_10;
	WristerEngine::ColorRGBA initColor;

	void ChangeScore();

public:
	// 静的初期化
	static void StaticInitialize();
	// 静的更新
	static void StaticUpdate();

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