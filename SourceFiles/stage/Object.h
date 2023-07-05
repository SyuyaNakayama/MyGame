#pragma once
#include "Collider.h"
#include "Model.h"

// �S�[���ɉ^�ԃI�u�W�F�N�g
class Object : public SphereCollider, public BoxCollider
{
	std::unique_ptr<Model> model;

public:
	void Initialize(Vector3 pos);
	void Update();
	void Draw();
	void OnCollision(SphereCollider* collider);
};