#pragma once
#include "ModelManager.h"

// �I�u�W�F�N�g�ɒǏ]����J����
class BaseCamera
{
protected:
	float distance = 50.0f; // �����_���王�_�܂ł̋���
	ViewProjection viewProjection;
	Vector2 angle = { 0,0.3f }; // �J������]��
	WorldTransform worldTransform;

public:
	virtual void Initialize(WorldTransform* parent);
	virtual void Update();
	ViewProjection* GetViewProjection() { return &viewProjection; }
	const Vector2& GetAngle() { return angle; }
};