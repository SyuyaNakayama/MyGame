#include "Physics.h"
#include <algorithm>
#include <imgui.h>
#include "ImGuiManager.h"
using namespace WristerEngine;

std::vector<std::array<Physics*, 2>> Physics::collideList;
float Physics::gravity = 0.5f; // �d�͉����x g
Vector3 Physics::gravityDir = { 0,-1,0 }; // �������d��
float Physics::k_air = 0.4f;

// �����N���X���� (Unity�ł��� Rigidbody)
std::unique_ptr<Physics> Physics::Create(_3D::Transform* w)
{
	std::unique_ptr<Physics> instance = std::make_unique<Physics>();
	instance->worldTransform = w;
	return instance;
}

void Physics::Backlash(const Vector3& wallNormal, float e)
{
	// ���̂̕ω���̑��x
	vel = -(1.0f + e) * Dot(vel + wallNormal, wallNormal) * wallNormal / 2.0f + vel;
}

void Physics::Backlash(Physics* p1, Physics* p2, float e)
{
	// �����Ƒ��肪�ՓˍςȂ珈�����X�L�b�v
	for (auto& collidedPair : collideList)
	{
		int isCollided = 0;
		for (size_t i = 0; i < collidedPair.size(); i++)
		{
			if (collidedPair[i] == p1) { isCollided |= 0b1; }
			if (collidedPair[i] == p2) { isCollided |= 0b10; }
		}
		if (isCollided == 0b11) { return; }
	}
	// �|�W�V�������擾
	Vector3 p1Pos = p1->worldTransform->GetWorldPosition();
	Vector3 p2Pos = p2->worldTransform->GetWorldPosition();
	// �Փ˂̖@���x�N�g��
	Vector3 n = Normalize(p2Pos - p1Pos);
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
	collideList.push_back({ p1,p2 });
	// �����o������
	p1->vel += Normalize(p1Pos - p2Pos) * 0.25f;
	p2->vel += Normalize(p2Pos - p1Pos) * 0.25f;
}

void Physics::Update()
{
	accel = force / mass; // �����x���v�Z
	vel += accel * forceDir; // ���x�ɉ����x�����Z
	worldTransform->translation += vel; // �ʒu�ɑ��x���Z

	// ��������
	if (isFreeFall)
	{
		fallSpd += gravity;
		fallSpd -= k_air * fallSpd / mass;
		fallSpd = max(fallSpd, 0);
		vel += fallSpd * gravityDir;
	}
	// �ڒn����
	else
	{
		// ���C��\��
		float friction = mu * mass * gravity; // ���C��
		float nextSpd = max(vel.Length() - friction, 0);
		vel = Normalize(vel) * nextSpd;
	}
}

void Physics::SetMass(float m)
{
	assert(m > 0);
	mass = m;
}