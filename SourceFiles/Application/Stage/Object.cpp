#include "Object.h"
#include "ModelManager.h"
#include <imgui.h>
#include "ParticleManager.h"
#include "Stage.h"

int Object::instanceNum = 0;

void Object::Initialize(const ObjectData& objectData)
{
	object = ModelManager::Create("player", true);
	object->worldTransform.reset(objectData.worldTransform);
	object->material.ambient = { 0,0,0 };
	object->material.SetSprite(Sprite::Create("DissolveMap.png"), TexType::Dissolve);
	worldTransform = object->worldTransform.get();
	collisionAttribute = CollisionAttribute::Object;
	collisionMask = CollisionMask::Object;
	physics = Physics::Create(worldTransform);
	physics->SetMass(0.5f);
	physics->SetMu(0.05f);
	physics->SetIsFreeFall(true);
}

void Object::Update()
{
	// —Ž‰ºŒã‚ÌYŽ²ŒÅ’è‰»
	if (!physics->IsFreeFall()) { worldTransform->translation.y = Stage::GROUND_POS_Y; }
	if (!isGoal) { physics->Update(); return; }
	const float DISSOLVE_POW_INC = 0.05f;
	dissolvePow += DISSOLVE_POW_INC;
	object->material.SetDissolvePow(dissolvePow);
	if (dissolvePow >= 1.0f) { Destroy(); }
}

void Object::OnCollision(SphereCollider* collider)
{
	Physics* _physics = collider->GetPhysics();
	if (!_physics) { return; }

	// ’e«Õ“Ë
	Physics::Backlash(physics.get(), _physics, 1.0f);

	DiffuseParticle::AddProp addProp;
	addProp.addNum = 10;
	addProp.start_scale = 5;
	addProp.posOffset = worldTransform->translation;
	ParticleGroup* particleGroup = ParticleManager::GetParticleGroup(1);
	particleGroup->Add(addProp);
}