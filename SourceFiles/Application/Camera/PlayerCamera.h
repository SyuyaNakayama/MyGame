#pragma once
#include "BaseCamera.h"

class PlayerCamera : public BaseCamera
{
	Vector3 parentPrePos;
	
	void Initialize(WorldTransform* parent);
	void Update();
};