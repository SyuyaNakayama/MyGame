#pragma once
#include "Collider.h"

// ゴールに運ぶオブジェクト
class Object : public SphereCollider
{
	std::unique_ptr<Model> model;

public:
	void Initialize();
	void Update();
	void Draw();

};