#pragma once
#include "Collider.h"
#include "GameObject.h"

// ゴールに運ぶオブジェクト
class Object : public SphereCollider, public BoxCollider, public GameObject
{
	Object3d* object;
	bool isGoal = false;
	float dissolvePow = 0;
	static int instanceNum;

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
	bool IsDestroy() { return object->isDestroy; }
	// このクラスのインスタンス数を取得
	static int GetInstanceNum() { return instanceNum; }
	// ゴールした
	void Goal() { isGoal = true; }
};