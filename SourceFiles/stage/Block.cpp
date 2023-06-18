#include "Block.h"

void Block::Initialize(Vector3 scale, Vector3 position, Vector3 planeNormal, float distance_)
{
	model = Model::Create("cube");
	Sprite* modelSprite = model->GetMaterial()->GetSprite();
	modelSprite->textureSize.x *= scale.x / 5.0f;
	modelSprite->textureSize.y *= scale.z / 5.0f;
	model->Update();
	worldTransform.Initialize();
	worldTransform.scale = scale;
	worldTransform.translation = position;
	worldTransform.Update();
	baseNormal = planeNormal;
	distance = distance_;
}

void Block::Update()
{

}

void Block::Draw()
{
	model->Draw(worldTransform);
}

void Block::OnCollision(SphereCollider* collider)
{
	Vector3 v = collider->GetPhysics()->GetVelocity();
	Vector3 n = GetNormal();
	Vector3 vel = -(Dot(v + n, n)) * n + v;
	collider->GetPhysics()->SetVelocity(vel);
}