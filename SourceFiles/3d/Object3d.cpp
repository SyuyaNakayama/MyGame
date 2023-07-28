#include "Object3d.h"
#include "ModelManager.h"

void Object3d::Initialize(Mesh* mesh_)
{
	mesh = mesh_;
	material.Load(mesh_);
	worldTransform.Initialize();
}

void Object3d::Update()
{
	material.Update();
	worldTransform.Update();
}

void Object3d::Draw()
{
	ID3D12GraphicsCommandList* cmdList = DirectXCommon::GetInstance()->GetCommandList();
	cmdList->SetGraphicsRootConstantBufferView((UINT)RootParamNum::MatWorld, worldTransform.constBuffer->GetGPUVirtualAddress());
	worldTransform.isUpdated = false;
	material.Draw();
	mesh->Draw();
}