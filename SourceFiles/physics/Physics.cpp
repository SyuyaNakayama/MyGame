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

void Physics::Update()
{
	if (mass == 0) { return; } // 0�Ŋ���̂�j�~
	worldTransform->translation += vel; // �ʒu�ɑ��x���Z
	worldTransform->Update();
	forceDir.Normalize(); // �͂̌������K��
	accel = force / mass; // �^�������� F = ma �̉��p
	vel += accel * forceDir; // ���x�ɉ����x�����Z
	// ��������
	if (isFreeFall)
	{
		fallSpd += gravity - k_air * fallSpd / mass;
		vel += fallSpd * gravityDir;
	}
	ImGui::Text("PlayerSpd = %f", vel.Length());
	float friction = 1.0f - std::clamp(mu * mass * gravity, 0.0f, 1.0f); // ���C�� 
	// �ȈՓI�ɖ��C��\��
	vel *= friction;
}