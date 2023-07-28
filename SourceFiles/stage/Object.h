#pragma once
#include "Collider.h"
#include "Object3d.h"
#include "JsonLoader.h"

// ゴールに運ぶオブジェクト
class Object : public SphereCollider, public BoxCollider
{
	Object3d* object;
	bool isDestroy = false;

public:
	void Initialize(const ObjectData& objectData);
	void Update();
	void OnCollision(SphereCollider* collider);
	void Destroy() { isDestroy = true; } // 破壊する
	bool IsDestroy() { return isDestroy; }
};