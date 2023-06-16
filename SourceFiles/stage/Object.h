#pragma once
#include "Collider.h"

// �S�[���ɉ^�ԃI�u�W�F�N�g
class Object : public SphereCollider
{
	std::unique_ptr<Model> model;

public:
	void Initialize();
	void Update();
	void Draw();

};