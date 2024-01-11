#pragma once
#include "BaseScene.h"
#include "Scene.h"
#include <memory>

namespace WristerEngine
{
	// シーンファクトリーの抽象クラス
	class AbstractSceneFactory
	{
	public:
		// 仮想デストラクタ
		virtual ~AbstractSceneFactory() = default;
		// シーン作成
		virtual std::unique_ptr<BaseScene> CreateScene(Scene scene) = 0;
	};
}