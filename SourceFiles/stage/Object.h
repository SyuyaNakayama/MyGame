#pragma once
#include "Collider.h"
#include "Model.h"
#include "JsonLoader.h"

// �S�[���ɉ^�ԃI�u�W�F�N�g
class Object : public SphereCollider, public BoxCollider
{
	std::unique_ptr<Model> model;
	bool isDestroy = false;

public:
	void Initialize(const ObjectData& objectData);
	void Update();
	void Draw();
	void OnCollision(SphereCollider* collider);
	void Destroy() { isDestroy = true; } // �j�󂷂�
	bool IsDestroy() { return isDestroy; }
};