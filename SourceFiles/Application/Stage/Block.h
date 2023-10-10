#pragma once
#include "Collider.h"
#include "GameObject.h"

class Block : public BoxCollider, public GameObject
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