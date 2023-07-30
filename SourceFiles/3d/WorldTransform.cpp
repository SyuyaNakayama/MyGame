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
	matWorld.InportVector(translation, 3);
	if (parent)
	{
		matWorld *= parent->matWorld; 
	}
	isUpdated = true;
	constMap->world = matWorld;
}