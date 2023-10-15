#pragma once
#include "Collider.h"
#include "GameObject.h"

// ���ƕǂ̃I�u�W�F�N�g
class Block : public BoxCollider, public GameObject
{
	Object3d* object;
	Vector3 normal;

public:
	void Initialize(const ObjectData& objectData);
	void Update();
	void OnCollision(BoxCollider* collider);
};

// �S�[���̃I�u�W�F�N�g
class Goal : public BoxCollider, public GameObject
{
	Object3d* object;
	Vector3 normal;

public:
	void Initialize(const ObjectData& objectData);
	void Update();
	void OnCollision(BoxCollider* collider);
};