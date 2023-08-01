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
	// �����Ƒ��肪�ՓˍςȂ珈�����X�L�b�v
	if (physics->IsCollided() && _physics->IsCollided())
	{
		physics->SetIsCollided(false);
		_physics->SetIsCollided(false);
		return;
	}

	// �e���Փ�
	Vector3 n = Normalize(collider->GetWorldPosition() - GetWorldPosition()); // �Փ˂̖@���x�N�g��
	Vector3 v0 = physics->GetVelocity(); // ���g�̍��̑��x
	Vector3 V0 = _physics->GetVelocity(); // ����̍��̑��x
	float m = physics->GetMass(); // ���g�̎���
	float M = _physics->GetMass(); // ����̎���
	float m_t = (2.0f * M * m) / (M + m); // ���x�v�Z�̋��ʕ���
	Vector3 v = -(m_t * Dot(v0 - V0, n) * n) / m + v0; // ���g�̕ω���̑��x
	Vector3 V = -(m_t * Dot(V0 - v0, n) * n) / m + V0; // ����̕ω���̑��x

	physics->SetVelocity(v);
	_physics->SetVelocity(V);
	physics->SetIsCollided(true);
	_physics->SetIsCollided(true);
}