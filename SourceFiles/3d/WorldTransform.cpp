#include "WorldTransform.h"
#include "D3D12Common.h"
#include <imgui.h>

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
	Matrix4 matTrans = Matrix4::Translate(translation);
	matWorld = matScale * matRot * matTrans;
	if (parent) { matWorld *= parent->matWorld; }
	isUpdated = true;
	constMap->world = matWorld;
}