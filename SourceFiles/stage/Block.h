#pragma once
#include "Collider.h"
#include "Model.h"

class Block : public BoxCollider
{
	std::unique_ptr<Model> model;

public:
	void Initialize(Vector3 scale, Vector3 position);
	void Update();
	void Draw();
};