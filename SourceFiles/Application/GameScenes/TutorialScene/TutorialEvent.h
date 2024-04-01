#pragma once
#include "SpriteAnimation.h"
#include <map>
#include "Constant.h"

// �`���[�g���A���̐���
class TutorialEvent
{
private:
	static const float TEX_SIZE_Y;
	// �`���[�g���A���̐���UI
	std::map<std::string, std::unique_ptr<WristerEngine::_2D::Sprite>> sprites;
	// �`���[�g���A���̐����ԍ�
	UINT32 phase = 0;
	WristerEngine::_2D::SpriteAnimation enter;
	WristerEngine::Constant* constant = WristerEngine::Constant::GetInstance();
	std::vector<UINT32> tutorialEventPhase;

	// �R���X�g���N�^�Ȃǂ�private��
	TutorialEvent() = default;
	~TutorialEvent() = default;

	// �G���^�[�L�[�������Ƃ��̃C�x���g�̐؂�ւ�
	void (TutorialEvent::* EnterEvent)() = nullptr;
	void EnterEventManager();

	// �q���g�\���؂�ւ�
	void PrintFlip();

public:
	TutorialEvent(const TutorialEvent& obj) = delete;
	TutorialEvent& operator=(const TutorialEvent& obj) = delete;

	static TutorialEvent* GetInstance();

	// ������
	void Initialize();
	// �X�V
	void Update();
	// �`��
	void Draw();
	// ���̃t�F�[�Y�֐i�߂�
	void NextPhase();
	/// <summary>
	/// phase���擾
	/// </summary>
	/// <returns>phase�l</returns>
	UINT32 GetPhase() const { return phase; }

	const std::vector<UINT32>* GetTutorialEventPhase() const { return &tutorialEventPhase; }
};