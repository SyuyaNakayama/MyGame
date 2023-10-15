#pragma once
#include "BaseScene.h"
#include "Scene.h"

// シーンファクトリーの抽象クラス
class AbstractSceneFactory
{
public:
	virtual ~AbstractSceneFactory() = default;
	virtual BaseScene* CreateScene(Scene scene) = 0;
};