#pragma once
#include "ScoreGauge.h"
#include "Easing.h"

// �����N�A�j���[�V�������N���X
class BaseAnimation
{
public:
	// ������
	virtual void Initialize() = 0;
	// �X�V
	virtual void Update() = 0;
	// �`��
	virtual void Draw() = 0;
};

// �����N�ƃX�R�A�̔���
class JudgeAnimation : public BaseAnimation
{
	// BaseAnimation ����Čp������܂���
	void Initialize() override;
	void Update() override;
	void Draw() override;
};

// ������
class DisappearAnimation : public BaseAnimation
{
	// BaseAnimation ����Čp������܂���
	void Initialize() override;
	void Update() override;
	void Draw() override;
};

// �����
class AppearAnimation : public BaseAnimation
{
	// BaseAnimation ����Čp������܂���
	void Initialize() override;
	void Update() override;
	void Draw() override;
};

// �ŏI�����N���\
class ResultAnimation : public BaseAnimation
{
	// BaseAnimation ����Čp������܂���
	void Initialize() override;
	void Update() override;
	void Draw() override;
};

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
	void Judge();
	void Disappear();
	void Appear();
	void Result();

public:
	// ������
	void Initialize(const ScoreGauge* pScoreGauge);
	// �X�V
	void Update();
	// �`��
	void Draw();
};