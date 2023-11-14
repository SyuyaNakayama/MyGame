#pragma once
#include "BaseSpawnPoint.h"
#include "Object.h"

// オブジェクト生成オブジェクト
class SpawnObject : public BaseSpawnPoint, public GameObject
{
	static std::list<std::unique_ptr<GameObject>>* objects;
	ObjectData objectData;
	Vector3 initialPos;
	static const int SPAWN_MAX = 300;

public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="objectData_">Jsonファイルから読み込んだデータ</param>
	void Initialize(const ObjectData& objectData_);
	// 更新
	void Update();
	// setter
	static void SetObjectList(std::list<std::unique_ptr<GameObject>>* list) { objects = list; }
};