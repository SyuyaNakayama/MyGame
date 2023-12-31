#include "ModelManager.h"
#include "Object.h"
#include "ParticleManager.h"
#include "Random.h"
#include "Stage.h"
#include <imgui.h>

int Object::instanceNum = 0;

void Object::Initialize(const ObjectData& objectData)
{
	object = ModelManager::Create("player", true);
	object->worldTransform.reset(objectData.worldTransform);
	Material* material = &object->material;
	material->ambient = { 0,0,0 };
	material->SetSprite(Sprite::Create("Textures/DissolveMap.png"), TexType::Dissolve);
	worldTransform = object->worldTransform.get();
	collisionAttribute = CollisionAttribute::Object;
	collisionMask = CollisionMask::Object;
	physics = Physics::Create(worldTransform);
	physics->SetMass(0.5f);
	physics->SetMu(0.05f);
	physics->SetIsFreeFall(true);

	// タイプの設定
	Random_Int rand(0, (int)Type::MaxNum);
	int num = rand();

	if (num < (int)Type::Red) { type = Type::White; }
	else if (num < (int)Type::Green) { type = Type::Red; }
	else { type = Type::Green; }

	switch (type)
	{
	case Type::Red:
		material->GetSprite(TexType::Main)->color = { 1,0,0,0 };
		break;
	case Type::Green:
		material->GetSprite(TexType::Main)->color = { 0,1,0,0 };
		break;
	}
}

void Object::Update()
{
	// 落下後のY軸固定化
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

	// 弾性衝突
	Physics::Backlash(physics.get(), _physics, 1.0f);

	DiffuseParticle::AddProp addProp;
	addProp.addNum = 10;
	addProp.start_scale = 5;
	addProp.posOffset = worldTransform->translation;
	ParticleGroup* particleGroup = ParticleManager::GetParticleGroup(1);
	particleGroup->Add(addProp);
}

int Object::GetGoalScore(int goalScore)
{
	switch (type)
	{
	case Type::White:	return goalScore;
	case Type::Red:		return goalScore * 2;
	case Type::Green:	return -goalScore;
	}
	return goalScore;
}