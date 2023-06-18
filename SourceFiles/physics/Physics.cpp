#include "Physics.h"
#include <algorithm>
#include <imgui.h>
#include "ImGuiManager.h"

float Physics::gravity = 1.0f;

std::unique_ptr<Physics> Physics::Create(WorldTransform* w)
{
	std::unique_ptr<Physics> instance = std::make_unique<Physics>();
	instance->worldTransform = w;
	return instance;
}

void Physics::Update()
{
	if (mass == 0) { return; } // 0‚ÅŠ„‚é‚Ì‚ð‘jŽ~
	worldTransform->translation += vel;
	worldTransform->Update();
	forceDir.Normalize();
	accel = force / mass;
	vel += accel * forceDir;
	float friction = 1.0f - std::clamp(mu * mass * gravity, 0.0f, 1.0f); // –€ŽC—Í
	// ŠÈˆÕ“I‚É–€ŽC‚ð•\Œ»
	vel *= friction;
}