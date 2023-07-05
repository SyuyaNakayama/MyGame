#include "Block.h"

void Block::Initialize(const ObjectData& objectData)
{
	model = Model::Create("cube");
	Sprite* modelSprite = model->GetMaterial()->GetSprite();
	modelSprite->textureSize.x *= objectData.scale.x / 5.0f;
	modelSprite->textureSize.y *= objectData.scale.z / 5.0f;
	model->Update();
	worldTransform = objectData;
	if (objectData.collider.type == "PLANE") { normal = objectData.collider.normal; }
	collisionAttribute = CollisionAttribute::Block;
	collisionMask = CollisionMask::Block;
}

void Block::Update()
{

}

void Block::Draw()
{
	model->Draw(worldTransform);
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