#pragma once
#include "Collider.h"
#include "Model.h"
#include "JsonLoader.h"

class Block : public BoxCollider
{
	std::unique_ptr<Model> model;
	Vector3 normal;

public:
	void Initialize(const ObjectData& objectData);
	void Update();
	void Draw();
	void OnCollision(BoxCollider* collider);
};