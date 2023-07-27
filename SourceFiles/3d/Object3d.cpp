#include "Object3d.h"

void Object3d::Initialize(const std::string& modelName)
{
	worldTransform.Initialize();
}

void Object3d::Update()
{
	worldTransform.Update();
}

void Object3d::Draw()
{
}
