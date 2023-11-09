#pragma once
#include "BaseScene.h"
#include "RankAnimation.h"

// ���ʔ��\�V�[���̏���
class ResultScene : public BaseScene
{
	// ������(�I�[�o�[���C�h)
	void Initialize();
	// �X�V(�I�[�o�[���C�h)
	void Update();
	// �`��(�I�[�o�[���C�h)
	void Draw();
};


// UI�`��N���X(���U���g�V�[���p)
class UIDrawerResultScene : public AbstractUIDrawer
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