#pragma once
#include "BaseScene.h"
#include "SpriteAnimation.h"
#include "Stage.h"

// �^�C�g���V�[���̏���
class TitleScene : public BaseScene
{
	Stage stage;
	ViewProjection camera;

	// ������(�I�[�o�[���C�h)
	void Initialize();
	// �X�V(�I�[�o�[���C�h)
	void Update();
	// �I��
	void Finalize() { stage.Finalize(); }
};

class UIDrawerTitleScene : public AbstractUIDrawer
{
	std::map<std::string, std::unique_ptr<Sprite>> title;
	SpriteAnimation spaceKey;
	std::unique_ptr<Sprite> selectCursorUI;
	Angle cosAngle = 0;
	std::unique_ptr<Sprite> sprite;

	// AbstractUIDrawer ����Čp������܂���
	void Initialize() override;
	void Update() override;
	void Draw() override;
};