#pragma once
#include "BaseScene.h"
#include "Sprite.h"

// ���ʔ��\�V�[���̏���
class ResultScene : public BaseScene
{
	std::unique_ptr<Sprite> sprite;

	// ������(�I�[�o�[���C�h)
	void Initialize();
	// �X�V(�I�[�o�[���C�h)
	void Update();
	// �`��(�I�[�o�[���C�h)
	void Draw();
};