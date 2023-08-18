#pragma once
#include "BaseSpawnPoint.h"
#include "Object.h"
#include "JsonLoader.h"
#include <ft2build.h>
#include FT_FREETYPE_H

class SpawnObject : public BaseSpawnPoint
{
	static std::list<std::unique_ptr<Object>>* objects;
	ObjectData objectData;
	Angle spawnPosAngle = 0;
	Vector3 initialPos;

public:
	void Initialize(const ObjectData& objectData_, int spawnInterval);
	void Spawn();
	static void SetObjectList(std::list<std::unique_ptr<Object>>* list) { objects = list; }
};