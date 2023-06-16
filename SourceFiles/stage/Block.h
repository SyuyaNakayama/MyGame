#pragma once
#include "Physics.h"

class Block : public Physics
{
	std::unique_ptr<Model> model;

public:
	void Initialize(Vector3 scale, Vector3 position);
	void Update();
	void Draw();
};