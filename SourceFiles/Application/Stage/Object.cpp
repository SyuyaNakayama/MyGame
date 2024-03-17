#include "ModelManager.h"
#include "Object.h"
#include "ParticleManager.h"
#include "Random.h"
#include "Stage.h"

using namespace WristerEngine::_2D;
using namespace WristerEngine::_3D;

int Object::instanceNum = 0;

void Object::Initialize(const WristerEngine::ObjectData& objectData)
{
	object = ModelManager::Create("player", true);
	object->worldTransform.reset(objectData.worldTransform);
	Material* material = &object->material;
	material->ambient = { 0,0,0 };
	material->SetSprite(Sprite::Create("Textures/DissolveMap.png"), TexType::Dissolve);
	worldTransform = object->worldTransform.get();
	collisionAttribute = CollisionAttribute::Object;
	collisionMask = CollisionMask::Object;
	physics = WristerEngine::Physics::Create(worldTransform);
	physics->SetMass(0.5f);
	physics->SetMu(0.05f);
	physics->SetIsFreeFall(true);
	type = objectData.objectType;

	switch (type)
	{
	case ObjectType::Red:
		material->GetSprite(TexType::Main)->color = { 1,0,0,0 };
		break;
	case ObjectType::Green:
		material->GetSprite(TexType::Main)->color = { 0,1,0,0 };
		break;
	}
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
	WristerEngine::Physics* _physics = collider->GetPhysics();
	if (!_physics) { return; }

	// ’e«Õ“Ë
	WristerEngine::Physics::Backlash(physics.get(), _physics, 1.0f);

	WristerEngine::DiffuseParticle::AddProp addProp;
	addProp.addNum = 10;
	addProp.start_scale = 5;
	addProp.posOffset = worldTransform->translation;
	WristerEngine::ParticleGroup* particleGroup = WristerEngine::ParticleManager::GetParticleGroup(1);
	particleGroup->Add(addProp);
}

int Object::GetGoalScore(int goalScore)
{
	switch (type)
	{
	case ObjectType::White:	return goalScore;
	case ObjectType::Red:	return goalScore * 2;
	case ObjectType::Green:	return -goalScore;
	}
	return goalScore;
}