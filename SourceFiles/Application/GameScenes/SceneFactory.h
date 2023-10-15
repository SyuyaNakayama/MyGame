#pragma once
#include "AbstractSceneFactory.h"

// 各シーンの生成クラス
class SceneFactory : public AbstractSceneFactory
{
private:
	SceneFactory() = default;

public:
	SceneFactory(const SceneFactory& obj) = delete;
	static SceneFactory* GetInstance();

	BaseScene* CreateScene(Scene scene) override;
};