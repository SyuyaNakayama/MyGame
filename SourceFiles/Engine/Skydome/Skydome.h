#pragma once
#include "Object3d.h"

// 天球オブジェクト
class Skydome
{
private:
	Object3d* object;

public:
	// 初期化
	void Initialize(float scale);
};