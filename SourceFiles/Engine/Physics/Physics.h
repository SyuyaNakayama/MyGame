#pragma once
#include "Transform.h"
#include <memory>
#include <array>

namespace WristerEngine
{
	// �����v�Z
	class Physics
	{
	private:
		static std::vector<std::array<Physics*, 2>> collideList;
		static float gravity; // �d�͉����x
		static Vector3 gravityDir; // �d�͂̌���
		static float k_air; // ��C��R�̔��萔
		_3D::Transform* worldTransform = nullptr;
		Vector3 vel; // ���x
		float accel = 0; // �����x
		float force = 0; // �͂̑傫��
		Vector3 forceDir; // �͂̌���
		float mass = 1;  // ����
		float mu = 0.1f; // ���C�W��
		bool isFreeFall = false; // ���R�����t���O
		float fallSpd = 0; // �������x

	public:
		/// <summary>
		/// �C���X�^���X����
		/// </summary>
		/// <param name="w">���[���h�g�����X�t�H�[��</param>
		/// <returns>�C���X�^���X</returns>
		static std::unique_ptr<Physics> Create(_3D::Transform* w);
		// �������̂Ɠ����Ȃ����̂̔�����̑��x���v�Z
		void Backlash(const Vector3& wallNormal, float e);
		// ����2���̂̔�����̑��x���v�Z
		static void Backlash(Physics* p1, Physics* p2, float e);
		// �d�͉����x��ݒ�
		static void SetGravity(float g) { gravity = g; }
		// �Փˏ������s��������Z�b�g
		static void ResetCollideList() { collideList.clear(); }
		// �X�V
		void Update();
		// setter
		Vector3 SetVelocity(Vector3 velocity) { return vel = velocity; }
		void SetForce(float f) { force = f; }
		void SetForceDir(Vector3 dir) { forceDir = Normalize(dir); } // dir�͎����I�ɐ��K�������
		void SetMass(float m);
		void SetMu(float mu_) { mu = mu_; }
		void SetIsFreeFall(bool isFreeFall_) { isFreeFall = isFreeFall_; }
		// getter
		const Vector3& GetVelocity() const { return vel; }
		float GetForce() const { return accel * mass; }
		float GetMass() const { return mass; }
		_3D::Transform* GetWorldTransform() { return worldTransform; }
		bool IsFreeFall() const { return isFreeFall; }
		float GetMomentum() const { return mass * vel.Length(); } // �^���ʂ��擾
	};
}