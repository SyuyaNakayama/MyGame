#pragma once
#include "BaseScene.h"
#include "BitMapNumber.h"

// UI�`��N���X(���U���g�V�[���p)
class UIDrawerResultScene : public AbstractUIDrawer
{
private:
	std::unique_ptr<Sprite> rankGauge;
	std::unique_ptr<Sprite> rankGaugeBG;
	std::unique_ptr<Sprite> scoreUI;
	int score;
	int printScore; // ���\������Ă�Q�[�W��
	BitMapNumber printScoreUI; // ���\������Ă�Q�[�W�ʂ�UI
	const Vector2 GAUGE_SIZE = { 641,40 };
	const int GAUGE_MAX_SCORE = 3000;
	const int GAUGE_INC_SPD = 15; // �Q�[�W�㏸���x

public:
	// ������(�I�[�o�[���C�h)
	void Initialize();
	// �X�V(�I�[�o�[���C�h)
	void Update();
	// �`��(�I�[�o�[���C�h)
	void Draw();
};


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