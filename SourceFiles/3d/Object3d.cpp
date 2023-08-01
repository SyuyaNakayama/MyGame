#include "Object3d.h"
#include "ModelManager.h"

void Object3d::Initialize(Mesh* mesh_)
{
	mesh = mesh_;
	material.Load(mesh_);
	worldTransform = std::make_unique<WorldTransform>();
	worldTransform->Initialize();
}

void Object3d::Update()
{
	material.Update();
	worldTransform->Update();
}

void Object3d::Draw()
{
	worldTransform->Draw();
	material.Draw();
	mesh->Draw();
}