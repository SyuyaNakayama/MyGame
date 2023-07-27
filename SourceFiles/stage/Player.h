#pragma once
#include "Collider.h"
#include "PlayerCamera.h"
#include "JsonLoader.h"

class Player : public SphereCollider, public BoxCollider
{
	std::unique_ptr<Object3d> object;
	std::unique_ptr<BaseCamera> camera;

	void Move();

public:
	void Initialize(const ObjectData& objectData);
	void Update();
	void Draw();
};