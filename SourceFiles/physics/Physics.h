#pragma once
#include "WorldTransform.h"

// �����v�Z
class Physics
{
private:
	static float gravity;
	WorldTransform* worldTransform = nullptr;
	Vector3 vel; // ���x
	float accel = 0; // �����x
	float force = 0; // �͂̑傫��
	Vector3 forceDir; // �͂̌���
	float mass = 1;  // ����
	float mu = 0.1f; // ���C�W��

public:
	static void SetGravity(float g) { gravity = g; }
	void SetWorldTransform(WorldTransform* w) { worldTransform = w; }
	void SetMass(float m) { mass = m; }
	void SetForce(float f) { force = f; }
	void SetForceDir(Vector3 dir) { forceDir = dir; }
	void SetMu(float mu_) { mu = mu_; }
	void Update();
};