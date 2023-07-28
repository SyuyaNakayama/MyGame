#pragma once
#include "Collider.h"
#include "Object3d.h"
#include "JsonLoader.h"

class Block : public BoxCollider
{
	Object3d* object;
	Vector3 normal;

public:
	void Initialize(const ObjectData& objectData);
	void Update();
	void OnCollision(BoxCollider* collider);
};

class Goal : public BoxCollider
{
	Object3d* object;
	Vector3 normal;

public:
	void Initialize(const ObjectData& objectData);
	void Update();
	void OnCollision(BoxCollider* collider);
};