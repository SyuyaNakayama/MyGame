#pragma once
#include "AbstractSceneFactory.h"

// �e�V�[���̐����N���X
class SceneFactory : public AbstractSceneFactory
{
private:
	SceneFactory() = default;

public:
	SceneFactory(const SceneFactory& obj) = delete;
	static SceneFactory* GetInstance();

	BaseScene* CreateScene(Scene scene) override;
};