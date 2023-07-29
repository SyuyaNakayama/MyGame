#include "WorldTransform.h"
#include "D3D12Common.h"
#include "ImGuiManager.h"

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
	matWorld.m[3][0] = translation.x;
	matWorld.m[3][1] = translation.y;
	matWorld.m[3][2] = translation.z;
	if (parent) { matWorld *= parent->matWorld; }
	isUpdated = true;
	constMap->world = matWorld;
}