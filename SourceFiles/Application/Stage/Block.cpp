#include "Block.h"
#include "Stage.h"
#include "ParticleManager.h"

void Block::Initialize(const ObjectData& objectData)
{
	object = ModelManager::Create("cube");
	object->worldTransform.reset(objectData.worldTransform);
	worldTransform = object->worldTransform.get();
	Material& material = object->material;
	material.ambient = { 0,0,0 };
	material.diffuse = { 1,1,1 };
	material.specular = { 0,0,0 };
	Sprite* objectSprite = material.GetSprite(TexType::Main);

	const float WALL_SPLIT_NUM = 5.0f;
	objectSprite->textureSize.x *= worldTransform->scale.x / WALL_SPLIT_NUM;
	objectSprite->textureSize.y *= worldTransform->scale.z / WALL_SPLIT_NUM;
	
	if (objectData.collider.type == "PLANE") { normal = objectData.collider.normal; }
	if (objectData.fileName == "Ground") { collisionAttribute = CollisionAttribute::Ground; }
	else { collisionAttribute = CollisionAttribute::Block; }
	collisionMask = CollisionMask::Block;
}

void Block::OnCollision(BoxCollider* collider)
{
	Physics* physics_ = collider->GetPhysics();
	if (!physics_) { return; }
	const float ZERO = 0.001f;
	if (normal.Length() <= ZERO) { return; }
	if (collisionAttribute == CollisionAttribute::Ground && physics_->IsFreeFall())
	{
		physics_->SetIsFreeFall(false);
		physics_->SetVelocity({});
		physics_->GetWorldTransform()->translation.y = worldTransform->GetWorldPosition().y + worldTransform->scale.y;
		return;
	}
	if (collisionAttribute == CollisionAttribute::Block)
	{
		physics_->Backlash(normal, 1.0f);
	}
}

void Goal::Initialize(const ObjectData& objectData)
{
	object = ModelManager::Create("cube");
	object->worldTransform.reset(objectData.worldTransform);
	worldTransform = object->worldTransform.get();
	Material& material = object->material;
	material.SetSprite(Sprite::Create("white1x1.png"), TexType::Main);
	//material.ambient = { 1,1,1 };
	material.ambient = { 0.2f,0.2f,0.2f };
	if (objectData.collider.type == "PLANE") { normal = objectData.collider.normal; }
	collisionAttribute = CollisionAttribute::Goal;
	collisionMask = CollisionMask::Goal;
}

void Goal::OnCollision(BoxCollider* collider)
{
	Physics* physics_ = collider->GetPhysics();
	if (!physics_) { return; }
	if (normal.Length() <= 0.001f) { return; }
	if (collider->GetCollisionAttribute() == CollisionAttribute::Player)
	{
		physics_->Backlash(normal, 1.0f);
	}
	else if (collider->GetCollisionAttribute() == CollisionAttribute::Object)
	{
		Object* object_ = dynamic_cast<Object*>(collider);
		assert(object_);
		collider->SetCollisionMask(CollisionMask::None);
		object_->Goal();
		const int SCORE_INC = 10;
		Stage::AddScore(SCORE_INC);

		ParticleGroup* pGroup = ParticleManager::GetParticleGroup(0);
		DiffuseParticle::AddProp addProp;
		addProp.addNum = 30;
		addProp.start_scale = 10;
		addProp.posOffset = collider->GetWorldPosition();
		addProp.accOffset.y = 0.01f;
		pGroup->Add(addProp);
	}
}