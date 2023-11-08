#pragma once
#include "BaseScene.h"
#include "BitMapNumber.h"
#include "Easing.h"
#include <map>

// UI�`��N���X(���U���g�V�[���p)
class UIDrawerResultScene : public AbstractUIDrawer
{
private:
	// �����N�Ɠ_��
	static const int GAUGE_MAX_SCORE = 3000;
	const Vector2 GAUGE_SIZE = { 641,40 };
	const int GAUGE_INC_SPD = 15; // �Q�[�W�㏸���x
	const int RANK_ANIMATION_TIME = 10;

	enum class Rank
	{
		MAX = GAUGE_MAX_SCORE,
		S = Rank::MAX * 9 / 10,
		A = Rank::MAX * 7 / 10,
		B = Rank::MAX * 5 / 10,
		C = Rank::MAX * 0 / 10
	};

	std::unique_ptr<Sprite> scoreUI;
	int score = 0;
	int printScore = 0; // ���\������Ă�Q�[�W��
	BitMapNumber printScoreUI; // ���\������Ă�Q�[�W�ʂ�UI

	std::unique_ptr<Sprite> rankGauge;
	std::unique_ptr<Sprite> rankGaugeBG;
	std::unique_ptr<Sprite> resultRankSprite;
	std::map<Rank, std::unique_ptr<Sprite>> rankGaugeSplit;
	std::map<Rank, std::unique_ptr<Sprite>> rankUI;
	std::unique_ptr<Sprite> blind; // ��ʂ��Â�����
	Rank preRank;
	Easing rankSpriteFade;
	Easing rankSpriteScale;
	Vector2 rankSpriteSizeMem;

	// �X�R�A�\���֘A�̏�����
	void ScoreInitialize();
	// �X�R�A�\���֘A�̍X�V
	void ScoreUpdate();
	// �X�R�A�����j�^�[���W�ɕϊ�
	float ScoreToMoniter(int score_) { return min((float)score_ * GAUGE_SIZE.x / GAUGE_MAX_SCORE, GAUGE_SIZE.x); }
	// �����N�\���֘A�̏�����
	void RankInitialize();
	// �����N�\���֘A�̍X�V
	void RankUpdate();
	// �����N�A�j���[�V�����̊֐��|�C���^
	void (UIDrawerResultScene::* RankAnimation)() = &UIDrawerResultScene::Judge;
	// �����N�ƃX�R�A�̔���
	void Judge();
	// ������
	void Disappear();
	// �����
	void Appear();
	// �ŏI�����N���\
	void Result();
	// �����N���擾
	Rank GetRank(int score);

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