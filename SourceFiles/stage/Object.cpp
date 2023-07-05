#include "Object.h"

void Object::Initialize(Vector3 pos)
{
	model = Model::Create("player", true);
	worldTransform.Initialize();
	worldTransform.translation = pos;
	worldTransform.scale *= 4.0f;
	collisionAttribute = CollisionAttribute::Object;
	collisionMask = CollisionMask::Object;
	physics = Physics::Create(&worldTransform);
	physics->SetMass(0.5f);
	physics->SetMu(0);
}

void Object::Update()
{
	physics->Update();
	physics->SetForce(0);
}

void Object::Draw()
{
	model->Draw(worldTransform);
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
	float m_t = (2 * M * m) / (M + m); // 速度計算の共通部分
	Vector3 v = -(m_t * Dot(v0 - V0, n) * n) / m + v0; // 自身の変化後の速度
	Vector3 V = -(m_t * Dot(V0 - v0, n) * n) / m + V0; // 自身の変化後の速度
	physics->SetVelocity(v);
	_physics->SetVelocity(V);
	physics->SetIsCollided(true);
	_physics->SetIsCollided(true);
}