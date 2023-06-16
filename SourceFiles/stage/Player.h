#pragma once
#include "Physics.h"
#include "PlayerCamera.h"

class Player : public SphereCollider, public Physics
{
	std::unique_ptr<Model> model;
	std::unique_ptr<BaseCamera> camera;

	void Move();

public:
	void Initialize();
	void Update();
	void Draw();
};