#pragma once
#include "Sprite.h"

// �`���[�g���A���̐���
class TutorialEvent
{
private:
	static const float TEX_SIZE_Y;
	// �`���[�g���A���̃e�L�X�g�摜
	std::unique_ptr<WristerEngine::_2D::Sprite> text;
	// �`���[�g���A���̐����ԍ�
	UINT32 phase = 0;

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