#pragma once
#include "Collider.h"
#include "Model.h"

// ゴールに運ぶオブジェクト
class Object : public SphereCollider, public BoxCollider
{
	std::unique_ptr<Model> model;
	bool isDestroy = false;

public:
	void Initialize(Vector3 pos);
	void Update();
	void Draw();
	void OnCollision(SphereCollider* collider);
	void Destroy() { isDestroy = true; } // 破壊する
	bool IsDestroy() { return isDestroy; }
};