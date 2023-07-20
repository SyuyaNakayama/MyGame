#pragma once
#include "WorldTransform.h"
#include <memory>

// �����v�Z
class Physics
{
private:
	static float gravity;
	static Vector3 gravityDir; // �d�͂̌���
	static float k_air; // ��C��R�̔��萔
	WorldTransform* worldTransform = nullptr;
	Vector3 vel; // ���x
	float accel = 0; // �����x
	float force = 0; // �͂̑傫��
	Vector3 forceDir; // �͂̌���
	float mass = 1;  // ����
	float mu = 0.1f; // ���C�W��
	bool isCollided = false; // �Փˏ������s������
	bool isFreeFall = false; // ���R�����t���O
	float fallSpd = 0; // �������x

public:
	static std::unique_ptr<Physics> Create(WorldTransform* w);
	static void SetGravity(float g) { gravity = g; }
	void Update();
	Vector3 SetVelocity(Vector3 velocity) { return vel = velocity; }
	void SetForce(float f) { force = f; }
	void SetForceDir(Vector3 dir) { forceDir = Normalize(dir); } // dir�͎����I�ɐ��K�������
	void SetMass(float m) { mass = m; }
	void SetMu(float mu_) { mu = mu_; }
	void SetIsFreeFall(bool isFreeFall_) { isFreeFall = isFreeFall_; }
	Vector3 GetVelocity() { return vel; }
	float GetForce() { return accel * mass; }
	float GetMass() { return mass; }
	float GetMomentum() { return mass * vel.Length(); } // �^���ʂ��擾
	void SetIsCollided(bool isCollided_) { isCollided = isCollided_; }
	bool IsCollided() { return isCollided; }
};