#pragma once
#include "BitMapNumber.h"
#include <map>

enum class Rank
{
	Max = 600,
	S = Max * 9 / 10,
	A = Max * 7 / 10,
	B = Max * 5 / 10,
	C = Max * 0 / 10
};

// �X�R�A�Q�[�W����
class ScoreGauge
{
private:
	const Vector2 GAUGE_SIZE = { 641,40 }; // �����N�Ɠ_��
	const int GAUGE_INC_SPD = 3; // �Q�[�W�㏸���x

	std::unique_ptr<WristerEngine::_2D::Sprite> scoreUI;
	int score = 0;
	int printScore = 0; // ���\������Ă�Q�[�W��
	WristerEngine::_2D::BitMapNumber printScoreUI; // ���\������Ă�Q�[�W�ʂ�UI

	std::unique_ptr<WristerEngine::_2D::Sprite> rankGauge;
	std::unique_ptr<WristerEngine::_2D::Sprite> rankGaugeBG;
	std::map<Rank, std::unique_ptr<WristerEngine::_2D::Sprite>> rankGaugeSplit;

public:
	// ������
	void Initialize();
	// �X�V
	void Update();
	// �`��
	void Draw();
	// �X�R�A�����j�^�[���W�ɕϊ�
	float ScoreToMoniter(int score_) { return min((float)score_ * GAUGE_SIZE.x / (float)Rank::Max, GAUGE_SIZE.x); }
	// �����N���擾
	Rank GetRank() const;
	// �O�̃����N���擾
	Rank GetPreRank() const;
	// �A�j���[�V�����̏I�����擾
	bool IsAnimationEnd() const { return score == printScore; }
};
