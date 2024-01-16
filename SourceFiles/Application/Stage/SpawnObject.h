#pragma once
#include "BaseSpawnPoint.h"
#include "Object.h"

// オブジェクト生成オブジェクト
class SpawnObject : public WristerEngine::BaseSpawnPoint, public WristerEngine::_3D::GameObject
{
	
	static std::list<std::unique_ptr<WristerEngine::_3D::GameObject>>* objects;
	WristerEngine::ObjectData objectData;
	Vector3 initialPos;
	static const int SPAWN_MAX = 25;

public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="objectData_">Jsonファイルから読み込んだデータ</param>
	void Initialize(const WristerEngine::ObjectData& objectData_);
	// 更新
	void Update();
	// setter
	static void SetObjectList(std::list<std::unique_ptr<WristerEngine::_3D::GameObject>>* list) { objects = list; }
};