#pragma once
#include "Vector.h"
#include "Collider.h"

enum class Primitive { Box, Sphere };

// �����v�Z
class Physics : public virtual BaseCollider
{
protected:
	static float gravity;
	Vector3 vel; // ���x
	float accel = 0; // �����x
	float force = 0; // �͂̑傫��
	Vector3 forceDir; // �͂̌���
	float mass = 1;  // ����
	float mu = 0.1f; // ���C�W��
	float rebE = 1.0f; // �����W�� -> rebound e

public:
	Physics();
	virtual ~Physics() = default;
	void Update();
	virtual void OnCollision(Physics* physics);
};