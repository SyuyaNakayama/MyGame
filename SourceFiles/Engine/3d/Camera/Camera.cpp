#include "Camera.h"
#include "D3D12Common.h"
#include <array>
using namespace WristerEngine;
using namespace _3D;

void Camera::Initialize(const CameraShake::Prop* shakeProp)
{
	CreateBuffer(constBuffer.GetAddressOf(), &constMap, (sizeof(ConstBufferData) + 0xff) & ~0xff);
	if (shakeProp) { shake = CameraShake::Create(*shakeProp); }
}

void Camera::Update()
{
	// �v���W�F�N�V�����s������߂�
	matProjection = Matrix4::Zero();
	matProjection.m[0][0] = 1.0f / (aspectRatio * std::tan(fovAngleY / 2.0f));
	matProjection.m[1][1] = 1.0f / std::tan(fovAngleY / 2.0f);
	matProjection.m[2][2] = farZ / (farZ - nearZ);
	matProjection.m[2][3] = 1.0f;
	matProjection.m[3][2] = -nearZ * farZ / (farZ - nearZ);

	// �V�F�C�N���v�Z
	Vector3 sTarget = target;
	Vector3 sEye = eye;
	if (shake)
	{
		Vector3 shakeVal = shake->Update();
		sTarget += shakeVal;
		sEye += shakeVal;
	}

	// �r���[�s������߂�
	std::array<Vector3, 3> axis;
	axis[(int)Axis::Z] = Normalize(sTarget - sEye);
	axis[(int)Axis::X] = Normalize(Cross(up, axis[(int)Axis::Z]));
	axis[(int)Axis::Y] = Normalize(Cross(axis[(int)Axis::Z], axis[(int)Axis::X]));
	Vector3 cameraMove;
	for (size_t i = 0; i < axis.size(); i++) { cameraMove[i] = Dot(sEye, axis[i]); }
	matView = Matrix4::CreateFromVector(axis[(int)Axis::X], axis[(int)Axis::Y], axis[(int)Axis::Z]);
	matView = Matrix4::Inverse(matView);
	for (size_t i = 0; i < axis.size(); i++) { matView.m[3][i] = -cameraMove[i]; }

	// 2�s����|����
	matViewProjection = matView * matProjection;

	// GPU�]��
	constMap->viewproj = matViewProjection;
	constMap->cameraPos = sEye;
}

void Camera::CameraMove(const Vector3& move)
{
	eye += move;
	target += move;
}