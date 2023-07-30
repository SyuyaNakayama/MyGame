#include "Block.h"
#include "Stage.h"

void Block::Initialize(const ObjectData& objectData)
{
	object = ModelManager::Create("cube");
	Material& material = object->material;
	material.ambient = { 0,0,0 };
	Sprite* objectSprite = material.GetSprite(TexType::Main);
	objectSprite->textureSize.x *= objectData.scale.x / 5.0f;
	objectSprite->textureSize.y *= objectData.scale.z / 5.0f;
	material.specular = { 0,0,0 };
	material.SetSprite(Sprite::Create("Scales.png"), TexType::Specular);
	worldTransform = &object->worldTransform;
	object->worldTransform = objectData;
	if (objectData.collider.type == "PLANE") { normal = objectData.collider.normal; }
	collisionAttribute = CollisionAttribute::Block;
	collisionMask = CollisionMask::Block;
}

void Block::Update()
{
	object->worldTransform.translation.y += 0.1f;
}

void Block::OnCollision(BoxCollider* collider)
{
	Physics* physics = collider->GetPhysics();
	if (!physics) { return; }
	if (normal.Length() <= 0.001f) { return; }
	Vector3 v = physics->GetVelocity();
	Vector3 vel = -(Dot(v + normal, normal)) * normal + v;
	collider->GetPhysics()->SetVelocity(vel);
}

void Goal::Initialize(const ObjectData& objectData)
{
	object = ModelManager::Create("cube");
	Material& material = object->material;
	material.SetSprite(Sprite::Create("white1x1.png"), TexType::Main);
	material.ambient = { 1,1,1 };
	material.diffuse = { 1,1,1 };
	Sprite* modelSprite = material.GetSprite(TexType::Main);
	modelSprite->textureSize.x *= objectData.scale.x / 5.0f;
	modelSprite->textureSize.y *= objectData.scale.z / 5.0f;
	worldTransform = &object->worldTransform;
	object->worldTransform = objectData;
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
		Vector3 v = physics->GetVelocity();
		Vector3 vel = -(Dot(v + normal, normal)) * normal + v;
		collider->GetPhysics()->SetVelocity(vel);
	}
	else if (collider->GetCollisionAttribute() == CollisionAttribute::Object)
	{
		Object* object = dynamic_cast<Object*>(collider);
		assert(object);
		object->Destroy();
		Stage::AddScore(10);
	}
}