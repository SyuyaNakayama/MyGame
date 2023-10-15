#pragma once
#include "BaseScene.h"
#include "Scene.h"

// �V�[���t�@�N�g���[�̒��ۃN���X
class AbstractSceneFactory
{
public:
	// ���z�f�X�g���N�^
	virtual ~AbstractSceneFactory() = default;
	// �V�[���쐬
	virtual BaseScene* CreateScene(Scene scene) = 0;
};