#include "Physics.h"
#include <algorithm>
#include <imgui.h>
#include "ImGuiManager.h"

float Physics::gravity = 1.0f; // 重力加速度 g

// 物理クラス生成 (Unityでいう Rigidbody)
std::unique_ptr<Physics> Physics::Create(WorldTransform* w)
{
	std::unique_ptr<Physics> instance = std::make_unique<Physics>();
	instance->worldTransform = w;
	return instance;
}

void Physics::Update()
{
	if (mass == 0) { return; } // 0で割るのを阻止
	worldTransform->translation += vel; // 位置に速度加算
	worldTransform->Update();
	forceDir.Normalize(); // 力の向き正規化
	accel = force / mass; // 運動方程式 F = ma の応用
	vel += accel * forceDir; // 速度に加速度を加算
	float friction = 1.0f - std::clamp(mu * mass * gravity, 0.0f, 1.0f); // 摩擦力 
	// 簡易的に摩擦を表現
	vel *= friction;
}