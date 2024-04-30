#pragma once
#include "BaseScene.h"
#include "SpriteAnimation.h"
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
	std::map<std::string, std::unique_ptr<WristerEngine::_2D::Sprite>> title;
	std::unique_ptr<WristerEngine::_2D::SpriteAnimation> operateKey;
	std::unique_ptr<WristerEngine::_2D::Sprite> selectCursorUI;
	Angle cosAngle = 0;

	// AbstractUIDrawer ����Čp������܂���
	void Initialize() override;
	void Update() override;
	void Draw() override;
};