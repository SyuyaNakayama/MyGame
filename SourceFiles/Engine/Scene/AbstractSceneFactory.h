#pragma once
#include "BaseScene.h"
#include "Scene.h"
#include <memory>

namespace WristerEngine
{
	// �V�[���t�@�N�g���[�̒��ۃN���X
	class AbstractSceneFactory
	{
	public:
		// ���z�f�X�g���N�^
		virtual ~AbstractSceneFactory() = default;
		// �V�[���쐬
		virtual std::unique_ptr<BaseScene> CreateScene(Scene scene) = 0;
	};
}