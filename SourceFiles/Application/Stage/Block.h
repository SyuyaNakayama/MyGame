#pragma once
#include "Collider.h"
#include "GameObject.h"

// 床と壁のオブジェクト
class Block : public BoxCollider, public GameObject
{
	Object3d* object;
	Vector3 normal;

public:
	void Initialize(const ObjectData& objectData);
	void Update();
	void OnCollision(BoxCollider* collider);
};

// ゴールのオブジェクト
class Goal : public BoxCollider, public GameObject
{
	Object3d* object;
	Vector3 normal;

public:
	void Initialize(const ObjectData& objectData);
	void Update();
	void OnCollision(BoxCollider* collider);
};