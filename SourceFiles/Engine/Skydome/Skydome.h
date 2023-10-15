#pragma once
#include "Object3d.h"

// 天球オブジェクト
class Skydome
{
private:
	Object3d* object;

public:
	void Initialize(float scale);
};