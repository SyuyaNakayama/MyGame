#pragma once
#include "WorldTransform.h"
#include <memory>
#include <array>

// �����v�Z
class Physics
{
private:
	static std::vector<std::array<Physics*, 2>> collideList;
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
	bool isFreeFall = false; // ���R�����t���O
	float fallSpd = 0; // �������x

public:
	static std::unique_ptr<Physics> Create(WorldTransform* w);
	void Backlash(const Vector3& wallNormal, float e); // �������̂Ɠ����Ȃ����̂̔�����̑��x���v�Z
	static void Backlash(Physics* p1, Physics* p2, float e); // ����2���̂̔�����̑��x���v�Z
	static void SetGravity(float g) { gravity = g; }
	static void ResetCollideList() { collideList.clear(); } // �Փˏ������s��������Z�b�g

	void Update();
	
	Vector3 SetVelocity(Vector3 velocity) { return vel = velocity; }
	void SetForce(float f) { force = f; }
	void SetForceDir(Vector3 dir) { forceDir = Normalize(dir); } // dir�͎����I�ɐ��K�������
	void SetMass(float m);
	void SetMu(float mu_) { mu = mu_; }
	void SetIsFreeFall(bool isFreeFall_) { isFreeFall = isFreeFall_; }
	Vector3 GetVelocity() { return vel; }
	float GetForce() { return accel * mass; }
	float GetMass() { return mass; }
	WorldTransform* GetWorldTransform() { return worldTransform; }
	bool IsFreeFall() { return isFreeFall; }
	float GetMomentum() { return mass * vel.Length(); } // �^���ʂ��擾
};