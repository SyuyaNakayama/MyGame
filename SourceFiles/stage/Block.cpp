#include "Block.h"
#include "Stage.h"

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
	objectSprite->textureSize.x *= worldTransform->scale.x / 5.0f;
	objectSprite->textureSize.y *= worldTransform->scale.z / 5.0f;
	if (objectData.collider.type == "PLANE") { normal = objectData.collider.normal; }
	if (objectData.fileName == "Ground") { collisionAttribute = CollisionAttribute::Ground; }
	else { collisionAttribute = CollisionAttribute::Block; }
	collisionMask = CollisionMask::Block;
}

void Block::Update()
{
}

void Block::OnCollision(BoxCollider* collider)
{
	Physics* physics = collider->GetPhysics();
	if (!physics) { return; }
	if (normal.Length() <= 0.001f) { return; }
	if (collisionAttribute == CollisionAttribute::Ground && physics->IsFreeFall()) 
	{
		physics->SetIsFreeFall(false);
		physics->SetVelocity({});
		return; 
	}
	if (collisionAttribute == CollisionAttribute::Block)
	{
		physics->Backlash(normal, 1.0f);
	}
}

void Goal::Initialize(const ObjectData& objectData)
{
	object = ModelManager::Create("cube");
	object->worldTransform.reset(objectData.worldTransform);
	worldTransform = object->worldTransform.get();
	Material& material = object->material;
	material.SetSprite(Sprite::Create("white1x1.png"), TexType::Main);
	material.ambient = { 1,1,1 };
	if (objectData.collider.type == "PLANE") { normal = objectData.collider.normal; }
	collisionAttribute = CollisionAttribute::Goal;
	collisionMask = CollisionMask::Goal;
}

void Goal::Update()
{

}

void Goal::OnCollision(BoxCollider* collider)
{
	Physics* physics = collider->GetPhysics();
	if (!physics) { return; }
	if (normal.Length() <= 0.001f) { return; }
	if (collider->GetCollisionAttribute() == CollisionAttribute::Player)
	{
		physics->Backlash(normal, 1.0f);
	}
	else if (collider->GetCollisionAttribute() == CollisionAttribute::Object)
	{
		Object* object = dynamic_cast<Object*>(collider);
		assert(object);
		object->Destroy();
		Stage::AddScore(10);
	}
}