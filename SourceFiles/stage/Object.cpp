#include "Object.h"
#include "ModelManager.h"

void Object::Initialize(const ObjectData& objectData)
{
	object = ModelManager::Create("player", true);
	object->worldTransform.reset(objectData.worldTransform);
	object->material.ambient = { 0,0,0 };
	worldTransform = object->worldTransform.get();
	collisionAttribute = CollisionAttribute::Object;
	collisionMask = CollisionMask::Object;
	physics = Physics::Create(worldTransform);
	physics->SetMass(0.5f);
	//physics->SetMu(0.00f);
}

void Object::Update()
{
	physics->Update();
	physics->SetForce(0);
}

void Object::OnCollision(SphereCollider* collider)
{
	Physics* _physics = collider->GetPhysics();
	if (!_physics) { return; }
	// 自分と相手が衝突済なら処理をスキップ
	if (physics->IsCollided() && _physics->IsCollided())
	{
		physics->SetIsCollided(false);
		_physics->SetIsCollided(false);
		return;
	}

	// 弾性衝突
	Vector3 n = Normalize(collider->GetWorldPosition() - GetWorldPosition()); // 衝突の法線ベクトル
	Vector3 v0 = physics->GetVelocity(); // 自身の今の速度
	Vector3 V0 = _physics->GetVelocity(); // 相手の今の速度
	float m = physics->GetMass(); // 自身の質量
	float M = _physics->GetMass(); // 相手の質量
	float m_t = (2.0f * M * m) / (M + m); // 速度計算の共通部分
	Vector3 v = -(m_t * Dot(v0 - V0, n) * n) / m + v0; // 自身の変化後の速度
	Vector3 V = -(m_t * Dot(V0 - v0, n) * n) / m + V0; // 相手の変化後の速度

	physics->SetVelocity(v);
	_physics->SetVelocity(V);
	physics->SetIsCollided(true);
	_physics->SetIsCollided(true);
}