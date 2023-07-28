#pragma once
#include "Object3d.h"

class Skydome
{
private:
	Object3d* object;

public:
	void Initialize(float scale);
	void Update() { object->Update(); }
	void Draw() { object->Draw(); }
};