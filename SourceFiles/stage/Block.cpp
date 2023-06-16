#include "Block.h"

void Block::Initialize(Vector3 scale, Vector3 position)
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
}

void Block::Update()
{

}

void Block::Draw()
{
	model->Draw(worldTransform);
}