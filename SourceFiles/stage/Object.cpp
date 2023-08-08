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
	physics->SetMu(0.00f);
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

	// ’e«Õ“Ë
	Physics::Backlash(physics.get(), _physics, 1.0f);
}