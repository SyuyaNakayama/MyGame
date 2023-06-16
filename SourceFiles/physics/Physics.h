#pragma once
#include "Vector.h"
#include "Collider.h"

enum class Primitive { Box, Sphere };

// 物理計算
class Physics : public virtual BaseCollider
{
protected:
	static float gravity;
	Vector3 vel; // 速度
	float accel = 0; // 加速度
	float force = 0; // 力の大きさ
	Vector3 forceDir; // 力の向き
	float mass = 1;  // 質量
	float mu = 0.1f; // 摩擦係数
	float rebE = 1.0f; // 反発係数 -> rebound e

public:
	Physics();
	virtual ~Physics() = default;
	void Update();
	virtual void OnCollision(Physics* physics);
};