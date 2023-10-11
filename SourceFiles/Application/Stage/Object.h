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
	Object() { instanceNum++; }
	~Object() { instanceNum--; }
	void Initialize(const ObjectData& objectData);
	void Update();
	void OnCollision(SphereCollider* collider);
	void Destroy() { object->isDestroy = true; } // 破壊する
	bool IsDestroy() { return object->isDestroy; }
	static int GetInstanceNum() { return instanceNum; }
	void Goal() { isGoal = true; }
};