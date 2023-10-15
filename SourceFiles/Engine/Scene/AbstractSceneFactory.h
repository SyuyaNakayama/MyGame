#pragma once
#include "BaseScene.h"
#include "Scene.h"

// �V�[���t�@�N�g���[�̒��ۃN���X
class AbstractSceneFactory
{
public:
	virtual ~AbstractSceneFactory() = default;
	virtual BaseScene* CreateScene(Scene scene) = 0;
};