#include "Block.h"
#include "ModelManager.h"

using namespace WristerEngine::_2D;
using namespace WristerEngine::_3D;

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
	WristerEngine::Physics* physics_ = collider->GetPhysics();
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