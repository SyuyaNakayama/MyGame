#pragma once
#include "BaseScene.h"
#include "Sprite.h"
#include "Stage.h"
#include "CameraShake.h"

// �^�C�g���V�[���̏���
class TitleScene : public WristerEngine::BaseScene
{
	Stage stage;
	WristerEngine::_3D::Camera camera;

	// ������(�I�[�o�[���C�h)
	void Initialize();
	// �X�V(�I�[�o�[���C�h)
	void Update();
	// �I��
	void Finalize() { stage.Finalize(); }
};

class UIDrawerTitleScene : public WristerEngine::_2D::AbstractUIDrawer
{
	// AbstractUIDrawer ����Čp������܂���
	void Initialize() override;
	void Draw() override;
};