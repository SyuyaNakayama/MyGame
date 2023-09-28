#pragma once
#include "Collider.h"
#include "Object3d.h"
#include "JsonLoader.h"

// �S�[���ɉ^�ԃI�u�W�F�N�g
class Object : public SphereCollider, public BoxCollider
{
	Object3d* object;
	bool isGoal = false;
	float dissolvePow = 0;

public:
	void Initialize(const ObjectData& objectData);
	void Update();
	void OnCollision(SphereCollider* collider);
	void Destroy() { object->isDestroy = true; } // �j�󂷂�
	bool IsDestroy() { return object->isDestroy; }
	void Goal() { isGoal = true; }
};