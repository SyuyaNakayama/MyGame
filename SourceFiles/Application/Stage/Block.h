#pragma once
#include "Collider.h"
#include "GameObject.h"
#include "Random.h"

// 床と壁のオブジェクト
class Block : public BoxCollider, public GameObject
{
	Object3d* object;
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
class Goal : public BoxCollider, public GameObject
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
	static FrameTimer scoreChangeTimer;
	static bool isScoreChange;
	static Random_Int randScore;

	Object3d* object;
	Vector3 normal;
	Score score;
	ColorRGBA initColor;

	void ChangeScore();

public:
	// 静的初期化
	static void StaticInitialize() { scoreChangeTimer = 600; }
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