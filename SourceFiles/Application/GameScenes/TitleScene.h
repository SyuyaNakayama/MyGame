#pragma once
#include "BaseScene.h"
#include "SpriteAnimation.h"
#include "Stage.h"

// �^�C�g���V�[���̏���
class TitleScene : public BaseScene
{
	std::unique_ptr<Sprite> ui;
	Stage stage;
	ViewProjection camera;
	SpriteAnimation spaceKeyUI;

	// ������(�I�[�o�[���C�h)
	void Initialize();
	// �X�V(�I�[�o�[���C�h)
	void Update();
	// �`��(�I�[�o�[���C�h)
	void Draw();
};