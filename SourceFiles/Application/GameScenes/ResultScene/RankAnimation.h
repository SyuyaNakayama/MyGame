#pragma once
#include "ScoreGauge.h"
#include "Easing.h"
#include "SpriteAnimation.h"

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
	std::unique_ptr<WristerEngine::_2D::Sprite> rankUI;

public:
	// ���z�f�X�g���N�^
	virtual ~BaseAnimation() = default;
	// ������
	virtual void Initialize(RankAnimation* pRankAnimation);
	// �X�V
	virtual void Update() = 0;
	// �`��
	virtual void Draw() { rankUI->Draw(); }
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
};

// ������
class DisappearAnimation : public BaseAnimation
{
	WristerEngine::Easing rankSpriteFade;

	// BaseAnimation ����Čp������܂���
	void Initialize(RankAnimation* pRankAnimation) override;
	void Update() override;
};

// �����
class AppearAnimation : public BaseAnimation
{
	Vector2 rankSpriteSizeMem;
	WristerEngine::Easing rankSpriteFade;
	WristerEngine::Easing rankSpriteScale;

	// BaseAnimation ����Čp������܂���
	void Initialize(RankAnimation* pRankAnimation) override;
	void Update() override;
};

// �ŏI�����N���\
class ResultAnimation : public BaseAnimation
{
	Vector2 rankSpriteSizeMem;
	WristerEngine::Easing rankSpriteScale;
	WristerEngine::_2D::SpriteAnimation enterUI;
	std::unique_ptr<WristerEngine::_2D::Sprite> blind; // ��ʂ��Â�����

	void (ResultAnimation::* Phase)() = nullptr;
	void PrePushEnter();
	void PostPushEnter();

	// BaseAnimation ����Čp������܂���
	void Initialize(RankAnimation* pRankAnimation) override;
	void Update() override;
	void Draw() override;
};

// �A�j���[�V�����I��
class AnimationEnd : public BaseAnimation
{
	WristerEngine::_2D::SpriteAnimation spaceKey;
	// BaseAnimation ����Čp������܂���
	void Initialize(RankAnimation* pRankAnimation) override;
	void Update() override;
	void Draw() override;
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