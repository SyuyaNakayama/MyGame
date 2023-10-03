#pragma once
#include "BaseCamera.h"

// https://docs.google.com/presentation/d/1XNAtNpD0L91TbVdtewIjw1vmtithvjUjOqEj-8s6TSE/edit#slide=id.g22dd4f4a57f_0_213

class PlayerCamera : public BaseCamera
{
	Vector3 parentPrePos;
	
	void Initialize(WorldTransform* parent);
	void Update();
};