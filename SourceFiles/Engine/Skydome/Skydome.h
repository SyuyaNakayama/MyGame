#pragma once
#include "Object3d.h"

namespace WristerEngine
{
	// 天球オブジェクト
	class Skydome
	{
	private:
		Object3d* object;

	public:
		// 初期化
		void Initialize(float scale);
	};
}