#include "Physics.h"
#include <algorithm>
#include <imgui.h>
#include "ImGuiManager.h"

std::vector<std::array<Physics*, 2>> Physics::collideList;
float Physics::gravity = 0.5f; // 重力加速度 g
Vector3 Physics::gravityDir = { 0,-1,0 }; // 下向き重力
float Physics::k_air = 0.1f;

// 物理クラス生成 (Unityでいう Rigidbody)
std::unique_ptr<Physics> Physics::Create(WorldTransform* w)
{
	std::unique_ptr<Physics> instance = std::make_unique<Physics>();
	instance->worldTransform = w;
	return instance;
}

void Physics::Backlash(const Vector3& wallNormal, float e)
{
	// 物体の変化後の速度
	vel = -(1.0f + e) * Dot(vel + wallNormal, wallNormal) * wallNormal / 2.0f + vel;
}

void Physics::Backlash(Physics* p1, Physics* p2, float e)
{
	// 自分と相手が衝突済なら処理をスキップ
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
	// 衝突の法線ベクトル
	Vector3 n = Normalize(p1->worldTransform->GetWorldPosition() - p2->worldTransform->GetWorldPosition());
	// 2物体の速度
	Vector3 v0 = p1->vel;
	Vector3 V0 = p2->vel;
	// 2物体の質量
	float m = p1->mass;
	float M = p2->mass;
	// 速度計算の共通部分
	float m_t = ((1.0f + e) * M * m) / (M + m);
	// 2物体の変化後の速度
	Vector3 v = -(m_t * Dot(v0 - V0, n) * n) / m + v0;
	Vector3 V = -(m_t * Dot(V0 - v0, n) * n) / M + V0;
	p1->vel = v;
	p2->vel = V;
	collideList.push_back({ p1,p2 });
}

void Physics::Update()
{
	worldTransform->translation += vel; // 位置に速度加算

	accel = force / mass; // 運動方程式 F = ma の応用
	vel += accel * forceDir; // 速度に加速度を加算

	// 落下処理
	if (isFreeFall)
	{
		fallSpd += gravity;
		fallSpd -= k_air * fallSpd / mass;
		vel += fallSpd * gravityDir;
	}
	else
	{
		// 摩擦を表現
		float friction = mu * mass * gravity; // 摩擦力
		float nextSpd = max(vel.Length() - friction, 0);
		vel = Normalize(vel) * nextSpd;
	}
	//vel -= Normalize(vel) * k_air * vel.Length() / mass;
}

void Physics::SetMass(float m)
{
	assert(m > 0);
	mass = m;
}