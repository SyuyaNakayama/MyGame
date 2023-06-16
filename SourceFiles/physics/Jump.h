#pragma once
#include "Collider.h"

// �������܂�
class Jump : public RayCollider
{
private:
	float jumpSpd = 0;
	float gravity = 0;
	bool isJump = false;
	WorldTransform* pwt = nullptr;

public:
	void SetGravity(float gravity_) { gravity = gravity_; }
	void Start(float jumpV0);
	void Update();
	void SetWorldTransform(WorldTransform* worldTransform_){ pwt = worldTransform_; }
	const Vector3 GetRayDirection() { return { 0,-1,0 }; }
	void OnCollision(BoxCollider* collider);
};