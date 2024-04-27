#pragma once
#include "Input.h"
#include "DebugCamera.h"
#include "AbstractUIDrawer.h"
#include <memory>
#include "OperateConfig.h"

namespace WristerEngine
{
	class SceneManager;

	// �V�[�����N���X
	class BaseScene
	{
	protected:
		SceneManager* sceneManager = nullptr;
		Input* input = Input::GetInstance();
		_3D::DebugCamera debugCamera;
		std::unique_ptr<_2D::AbstractUIDrawer> uiDrawer;
		OperateConfig* operateConfig = OperateConfig::GetInstance();
		
	public:
		// �R���X�g���N�^
		BaseScene();
		virtual ~BaseScene() = default;
		// ������
		virtual void Initialize() = 0;
		// �X�V
		virtual void Update() = 0;
		// �`��
		virtual void Draw() { uiDrawer->Draw(); }
		// �I��
		virtual void Finalize() {}
	};
}