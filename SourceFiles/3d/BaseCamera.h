#pragma once
#include "ModelManager.h"

// オブジェクトに追従するカメラ
class BaseCamera
{
protected:
	float distance = 50.0f; // 注視点から視点までの距離
	ViewProjection viewProjection;
	Vector2 angle = { 0,0.3f }; // カメラ回転量
	WorldTransform worldTransform;

public:
	virtual void Initialize(WorldTransform* parent);
	virtual void Update();
	ViewProjection* GetViewProjection() { return &viewProjection; }
	const Vector2& GetAngle() { return angle; }
};