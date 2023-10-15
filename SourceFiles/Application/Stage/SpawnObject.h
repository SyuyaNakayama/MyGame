#pragma once
#include "BaseSpawnPoint.h"
#include "Object.h"

// オブジェクト生成オブジェクト
class SpawnObject : public BaseSpawnPoint, public GameObject
{
	static std::list<std::unique_ptr<GameObject>>* objects;
	ObjectData objectData;
	Angle spawnPosAngle = 0;
	Vector3 initialPos;
	float distance = 100;
	static const int SPAWN_MAX = 30;

public:
	void Initialize(const ObjectData& objectData_);
	void Update();
	static void SetObjectList(std::list<std::unique_ptr<GameObject>>* list) { objects = list; }
};