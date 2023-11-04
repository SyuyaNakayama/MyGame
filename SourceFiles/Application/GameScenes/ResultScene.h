#pragma once
#include "BaseScene.h"
#include "BitMapNumber.h"
#include <map>

// UI�`��N���X(���U���g�V�[���p)
class UIDrawerResultScene : public AbstractUIDrawer
{
private:
	// �����N�Ɠ_��
	static const int GAUGE_MAX_SCORE = 3000;
	enum class Rank
	{
		MAX = GAUGE_MAX_SCORE,
		S = Rank::MAX * 9 / 10,
		A = Rank::MAX * 7 / 10,
		B = Rank::MAX * 5 / 10,
		C = Rank::MAX * 0 / 10
	};

	std::unique_ptr<Sprite> rankGauge;
	std::unique_ptr<Sprite> rankGaugeBG;
	std::map<Rank, std::unique_ptr<Sprite>> rankGaugeSplit;
	std::map<Rank, std::unique_ptr<Sprite>> rankUI;
	std::unique_ptr<Sprite> scoreUI;
	int score;
	int printScore; // ���\������Ă�Q�[�W��
	BitMapNumber printScoreUI; // ���\������Ă�Q�[�W�ʂ�UI
	const Vector2 GAUGE_SIZE = { 641,40 };
	const int GAUGE_INC_SPD = 15; // �Q�[�W�㏸���x

	// �X�R�A�����j�^�[���W�ɕϊ�
	float ScoreToMoniter(int score_) { return min((float)score_ * GAUGE_SIZE.x / GAUGE_MAX_SCORE, GAUGE_SIZE.x); }

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