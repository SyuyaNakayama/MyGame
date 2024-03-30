#pragma once
#include "Collider.h"
#include "GameObject.h"
#include "TutorialEventManager.h"

// ゴールに運ぶオブジェクト
class Object : public WristerEngine::SphereCollider, public WristerEngine::BoxCollider, public WristerEngine::_3D::GameObject
{
private:
	static int instanceNum;

	WristerEngine::_3D::Object3d* object = nullptr;
	bool isGoal = false;
	float dissolvePow = 0;
	TutorialEventManager* eventManager = nullptr;
	ObjectType type = ObjectType::White;

public:
	// コンストラクタ
	Object() { instanceNum++; }
	// デストラクタ
	~Object() { instanceNum--; }
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="objectData">Jsonファイルから読み込んだデータ</param>
	void Initialize(const ObjectData& objectData);
	// 更新
	void Update();
	// 衝突コールバック関数(SphereCollider版)
	void OnCollision(SphereCollider* collider);
	// 破壊する
	void Destroy() { object->isDestroy = true; }
	// setter(isDestroy)
	bool IsDestroy() const { return object->isDestroy; }
	// このクラスのインスタンス数を取得
	static int GetInstanceNum() { return instanceNum; }
	// ゴールした
	void Goal() { isGoal = true; }
	/// <summary>
	/// ゴールに入れた時の点数を取得
	/// </summary>
	/// <param name="goalScore">ゴールの点数</param>
	/// <returns></returns>
	int GetGoalScore(int goalScore);
};