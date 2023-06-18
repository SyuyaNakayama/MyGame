#pragma once
#include "Collider.h"
#include "Model.h"

class Block : public PlaneCollider
{
	std::unique_ptr<Model> model;

public:
	void Initialize(Vector3 scale, Vector3 position, Vector3 planeNormal, float distance);
	void Update();
	void Draw();
	void OnCollision(SphereCollider* collider);
};