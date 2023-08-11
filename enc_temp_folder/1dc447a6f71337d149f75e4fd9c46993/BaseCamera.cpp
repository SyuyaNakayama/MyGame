#include "BaseCamera.h"
#include "ImGuiManager.h"

void BaseCamera::Initialize(WorldTransform* parent)
{
	worldTransform.Initialize();
	worldTransform.translation = { 0,10.0f,-10.0f };
	worldTransform.parent = parent;
	ModelManager::SetViewProjection(&viewProjection);
	viewProjection.Initialize();
}

void BaseCamera::Update()
{
	Vector3 eyeVec = -Vector3::MakeAxis(Axis::Z) * Matrix4::Rotate({ angle.y,angle.x }) * distance;
	worldTransform.translation = eyeVec;
	worldTransform.Update();
	viewProjection.target = worldTransform.parent->GetWorldPosition();
	viewProjection.eye = worldTransform.GetWorldPosition();
	ImGuiManager::PrintVector("EyePos", viewProjection.eye);
	worldTransform.isUpdated = false;
	Vector3 v1 = Normalize({ -1,1,0 });
	Vector3 v2 = Normalize({ 1,1,0 });
	Matrix4 mat = Matrix4::CreateFromVector({ 0,0,-1 }, { 0,1,0 }, { -1,0,0 }, { 1,0,0 });
	//Matrix4 mat = Matrix4::CreateFromVector({ 1,0,0 }, { 0,1,0 }, { 0,0,1 }, { 0,0,0 });
	Matrix4 mat2 = Matrix4::CreateFromVector({ 1,0,0 }, { 0,1,0 }, { 0,0,1 }, { 5,0,0 });
	mat = mat2 * mat;
	v1 *= mat;
	v2 *= mat;
	v1.Normalize();
	v2.Normalize();
	float d = Dot(v1, v2);
}