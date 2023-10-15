#pragma once
#include "Collider.h"
#include "GameObject.h"

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
	void Update(){}
	// 衝突コールバック関数(BoxCollider版)
	void OnCollision(BoxCollider* collider);
};

// ゴールのオブジェクト
class Goal : public BoxCollider, public GameObject
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