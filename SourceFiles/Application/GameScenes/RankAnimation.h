#pragma once
#include "ScoreGauge.h"
#include "Easing.h"

enum class AnimationPhase { Null, Judge, Disappear, Appear, Result, End };
// �O����`
class RankAnimation;

// �����N�A�j���[�V�������N���X
class BaseAnimation
{
protected:
	const int RANK_ANIMATION_TIME = 10;
	const ScoreGauge* pScoreGauge = nullptr;
	RankAnimation* pRankAnimation = nullptr;
	std::unique_ptr<Sprite> rankUI;

public:
	// ���z�f�X�g���N�^
	virtual ~BaseAnimation() = default;
	// ������
	virtual void Initialize(RankAnimation* pRankAnimation);
	// �X�V
	virtual void Update() = 0;
	// �`��
	virtual void Draw() = 0;
	// �����N�X�v���C�g�̐���
	void CreateRankUI(Rank rank);
};

// �����N�ƃX�R�A�̔���
class JudgeAnimation : public BaseAnimation
{
	Rank preRank;

	// BaseAnimation ����Čp������܂���
	void Initialize(RankAnimation* pRankAnimation) override;
	void Update() override;
	void Draw() override;
};

// ������
class DisappearAnimation : public BaseAnimation
{
	Easing rankSpriteFade;
	Easing rankSpriteScale;

	// BaseAnimation ����Čp������܂���
	void Initialize(RankAnimation* pRankAnimation) override;
	void Update() override;
	void Draw() override;
};

// �����
class AppearAnimation : public BaseAnimation
{
	Vector2 rankSpriteSizeMem;
	Easing rankSpriteFade;
	Easing rankSpriteScale;

	// BaseAnimation ����Čp������܂���
	void Initialize(RankAnimation* pRankAnimation) override;
	void Update() override;
	void Draw() override;
};

// �ŏI�����N���\
class ResultAnimation : public BaseAnimation
{
	std::unique_ptr<Sprite> blind; // ��ʂ��Â�����
	std::unique_ptr<Sprite> resultRankSprite;

	// BaseAnimation ����Čp������܂���
	void Initialize(RankAnimation* pRankAnimation) override;
	void Update() override;
	void Draw() override;
};

// �A�j���[�V�����I��
class AnimationEnd : public BaseAnimation
{
	// BaseAnimation ����Čp������܂���
	void Initialize(RankAnimation* pRankAnimation) override;
	void Update() override {};
	void Draw() override { rankUI->Draw(); };
};

// �����NUI�̃A�j���[�V����
class RankAnimation
{
private:
	AnimationPhase nextPhase = AnimationPhase::Null;
	const ScoreGauge* pScoreGauge = nullptr;

	// �A�j���[�V�����N���X
	std::unique_ptr<BaseAnimation> animation;

	// �A�j���[�V�����t�F�[�Y�̐؂�ւ�
	void ChangePhase();

public:
	// ������
	void Initialize(const ScoreGauge* pScoreGauge);
	// �X�V
	void Update();
	// �`��
	void Draw();
	// ���̃A�j���[�V�����t�F�[�Y�̗\��
	void ReservePhase(AnimationPhase next) { nextPhase = next; }
	// �X�R�A�Q�[�W�N���X�̃|�C���^���擾
	const ScoreGauge* GetScoreGauge() { return pScoreGauge; }
};