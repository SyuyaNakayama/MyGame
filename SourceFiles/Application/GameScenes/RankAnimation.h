#pragma once
#include "ScoreGauge.h"
#include "Easing.h"

class RankAnimation
{
private:
	const int RANK_ANIMATION_TIME = 10;

	std::unique_ptr<Sprite> resultRankSprite;
	std::map<Rank, std::unique_ptr<Sprite>> rankUI;
	std::unique_ptr<Sprite> blind; // ��ʂ��Â�����
	Rank preRank;
	Easing rankSpriteFade;
	Easing rankSpriteScale;
	Vector2 rankSpriteSizeMem;
	const ScoreGauge* pScoreGauge;

	// �����N�A�j���[�V�����̊֐��|�C���^
	void (RankAnimation::* Animation)() = &RankAnimation::Judge;
	// �����N�ƃX�R�A�̔���
	void Judge();
	// ������
	void Disappear();
	// �����
	void Appear();
	// �ŏI�����N���\
	void Result();

public:
	// ������
	void Initialize(const ScoreGauge* pScoreGauge);
	// �X�V
	void Update();
	// �`��
	void Draw();
};