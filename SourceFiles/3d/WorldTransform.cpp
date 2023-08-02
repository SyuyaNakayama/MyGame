#include "WorldTransform.h"
#include "D3D12Common.h"
#include "ModelManager.h"

void WorldTransform::Initialize()
{
	CreateBuffer(constBuffer.GetAddressOf(), &constMap, (sizeof(ConstBufferData) + 0xff) & ~0xff);
}

void WorldTransform::Update()
{
	if (parent) { parent->Update(); }
	if (isUpdated) { return; }
	Matrix4 matScale = Matrix4::Scale(scale);
	Matrix4 matRot = Matrix4::Rotate(rotation);
	matWorld = matScale * matRot;
	matWorld.SetVector(translation, 3);
	if (parent)
	{
		matWorld *= parent->matWorld;
	}
	isUpdated = true;
	constMap->world = matWorld;
}

void WorldTransform::Draw()
{
	ID3D12GraphicsCommandList* cmdList = DirectXCommon::GetInstance()->GetCommandList();
	cmdList->SetGraphicsRootConstantBufferView(
		(UINT)RootParamNum::MatWorld, constBuffer->GetGPUVirtualAddress());
	isUpdated = false;
}

Vector3 WorldTransform::GetScale()
{
	Vector3 scale;
	// グローバル行列からスケール値を抽出
	for (size_t i = 0; i < 3; i++) { scale[i] = matWorld.GetVector(i).Length(); }
	return scale;
}
