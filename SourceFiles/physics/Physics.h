#pragma once
#include "WorldTransform.h"

// 物理計算
class Physics
{
private:
	static float gravity;
	WorldTransform* worldTransform = nullptr;
	Vector3 vel; // 速度
	float accel = 0; // 加速度
	float force = 0; // 力の大きさ
	Vector3 forceDir; // 力の向き
	float mass = 1;  // 質量
	float mu = 0.1f; // 摩擦係数

public:
	static void SetGravity(float g) { gravity = g; }
	void SetWorldTransform(WorldTransform* w) { worldTransform = w; }
	void SetMass(float m) { mass = m; }
	void SetForce(float f) { force = f; }
	void SetForceDir(Vector3 dir) { forceDir = dir; }
	void SetMu(float mu_) { mu = mu_; }
	void Update();
};