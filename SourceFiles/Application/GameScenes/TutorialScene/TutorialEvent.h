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

	// �G���^�[�L�[�������Ƃ��̃C�x���g�̐؂�ւ�
	void (TutorialEvent::*EnterEvent)() = nullptr;
	void EnterEventManager();

	// �q���g�\���؂�ւ�
	void PrintFlip();

public:
	// ������
	void Initialize();
	// �X�V
	void Update();
	// �`��
	void Draw();
	// ���̃t�F�[�Y�֐i�߂�
	void NextPhase();
};