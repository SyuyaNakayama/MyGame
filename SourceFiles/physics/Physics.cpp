#include "Physics.h"
#include <algorithm>
#include "CollisionManager.h"
#include <imgui.h>
#include "ImGuiManager.h"

float Physics::gravity = 1.0f;

void Physics::Update()
{
	if (mass == 0) { return; } // 0‚ÅŠ„‚é‚Ì‚ð‘jŽ~
	worldTransform.translation += vel;
	forceDir.Normalize();
	accel = force / mass;
	vel += accel * forceDir;
	ImGui::Text("accel : %f", accel);
	ImGuiManager::PrintVector("vel", vel);
	OnCollision(nullptr);
}

Physics::Physics() { CollisionManager::PushCollider(this); }

void Physics::OnCollision(Physics* physics)
{
	float friction = 1.0f - std::clamp(mu * mass * gravity, 0.0f, 1.0f); // –€ŽC—Í
	// ŠÈˆÕ“I‚É–€ŽC‚ð•\Œ»
	vel *= friction;
}
