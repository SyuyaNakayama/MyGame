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
	physics->SetMu(0.00f);
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
	Vector3 V = -(m_t * Dot(V0 - v0, n) * n) / m + V0; // ���g�̕ω���̑��x
	physics->SetVelocity(v);
	_physics->SetVelocity(V);
	physics->SetIsCollided(true);
	_physics->SetIsCollided(true);
}