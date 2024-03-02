#pragma once
#include "BaseScene.h"
#include "RankAnimation.h"

// ���ʔ��\�V�[���̏���
class ResultScene : public WristerEngine::BaseScene
{
	// ������(�I�[�o�[���C�h)
	void Initialize();
	// �X�V(�I�[�o�[���C�h)
	void Update();
};

// UI�`��N���X(���U���g�V�[���p)
class UIDrawerResultScene : public WristerEngine::_2D::AbstractUIDrawer
{
private:
	ScoreGauge scoreGauge; 
	RankAnimation rankAnimation;

public:
	// ������(�I�[�o�[���C�h)
	void Initialize();
	// �X�V(�I�[�o�[���C�h)
	void Update();
	// �`��(�I�[�o�[���C�h)
	void Draw();
};