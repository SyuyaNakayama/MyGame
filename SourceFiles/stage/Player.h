#pragma once
#include "Collider.h"
#include "PlayerCamera.h"

class Player : public SphereCollider, public BoxCollider
{
	std::unique_ptr<Model> model;
	std::unique_ptr<BaseCamera> camera;

	void Move();

public:
	void Initialize();
	void Update();
	void Draw();
};