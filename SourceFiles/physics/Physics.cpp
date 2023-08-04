#include "Physics.h"
#include <algorithm>
#include <imgui.h>
#include "ImGuiManager.h"

float Physics::gravity = 0.5f; // �d�͉����x g
Vector3 Physics::gravityDir = { 0,-1,0 }; // �������d��
float Physics::k_air = 1.0f;

// �����N���X���� (Unity�ł��� Rigidbody)
std::unique_ptr<Physics> Physics::Create(WorldTransform* w)
{
	std::unique_ptr<Physics> instance = std::make_unique<Physics>();
	instance->worldTransform = w;
	return instance;
}

void Physics::Backlash(const Vector3& wallNormal, float e)
{
	Vector3 v = vel;
	// ���̂̕ω���̑��x
	Vector3 vel_ = -(1.0f + e) * Dot(v + wallNormal, wallNormal) * wallNormal / 2.0f + v;
	vel = vel_;
}

void Physics::Backlash(Physics* p1, Physics* p2, float e)
{
	// �Փ˂̖@���x�N�g��
	Vector3 n = Normalize(p1->worldTransform->GetWorldPosition() - p2->worldTransform->GetWorldPosition());
	// 2���̂̑��x
	Vector3 v0 = p1->vel;
	Vector3 V0 = p2->vel;
	// 2���̂̎���
	float m = p1->mass;
	float M = p2->mass;
	// ���x�v�Z�̋��ʕ���
	float m_t = ((1.0f + e) * M * m) / (M + m);
	// 2���̂̕ω���̑��x
	Vector3 v = -(m_t * Dot(v0 - V0, n) * n) / m + v0;
	Vector3 V = -(m_t * Dot(V0 - v0, n) * n) / M + V0;
	p1->vel = v;
	p2->vel = V;
	p1->isCollided = true;
	p2->isCollided = true;
}

void Physics::Update()
{
	if (mass == 0) { return; } // 0�Ŋ���̂�j�~
	worldTransform->translation += vel; // �ʒu�ɑ��x���Z

	forceDir.Normalize(); // �͂̌������K��
	accel = force / mass; // �^�������� F = ma �̉��p
	vel += accel * forceDir; // ���x�ɉ����x�����Z

	// ��������
	if (isFreeFall)
	{
		fallSpd += gravity - k_air * fallSpd / mass;
		vel += fallSpd * gravityDir;
	}
	else
	{
		// ���C��\��
		float friction = mu * mass * gravity; // ���C��
		float nextSpd = max(vel.Length() - friction, 0);
		vel = Normalize(vel) * nextSpd;
	}
}