#include "Block.h"
#include "Stage.h"

void Block::Initialize(const ObjectData& objectData)
{
	model = Model::Create("cube");
	model->GetMaterial()->SetAnbient({ 0,0,0 });
	Sprite* modelSprite = model->GetMaterial()->GetSprite(TexType::Main);
	modelSprite->textureSize.x *= objectData.scale.x / 5.0f;
	modelSprite->textureSize.y *= objectData.scale.z / 5.0f;
	model->GetMaterial()->SetSpecular({ 0,0,0 });
	model->GetMaterial()->SetSprite(Sprite::Create("Scales.png"), TexType::Specular);
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

void Goal::Initialize(const ObjectData& objectData)
{
	model = Model::Create("cube");
	Sprite* modelSprite = model->GetMaterial()->GetSprite(TexType::Main);
	modelSprite->textureSize.x *= objectData.scale.x / 5.0f;
	modelSprite->textureSize.y *= objectData.scale.z / 5.0f;
	model->Update();
	worldTransform = objectData;
	if (objectData.collider.type == "PLANE") { normal = objectData.collider.normal; }
	collisionAttribute = CollisionAttribute::Goal;
	collisionMask = CollisionMask::Goal;
	Material* material = model->GetMaterial();
	material->SetSprite(Sprite::Create("white1x1.png"), TexType::Main);
	material->SetAnbient({ 1,1,1 });
	material->SetDiffuse({ 1,1,1 });
	model->Update();
}

void Goal::Update()
{

}

void Goal::Draw()
{
	model->Draw(worldTransform);
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