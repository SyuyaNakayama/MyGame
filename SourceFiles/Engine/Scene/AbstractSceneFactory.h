#pragma once
#include "BaseScene.h"
#include "Scene.h"

// シーンファクトリーの抽象クラス
class AbstractSceneFactory
{
public:
	// 仮想デストラクタ
	virtual ~AbstractSceneFactory() = default;
	// シーン作成
	virtual BaseScene* CreateScene(Scene scene) = 0;
};