#pragma once
#include "Sprite.h"
#include <map>

// �`���[�g���A���̐���
class TutorialEvent
{
private:
	static const float TEX_SIZE_Y;
	// �`���[�g���A���̐���UI
	std::map<std::string, std::unique_ptr<WristerEngine::_2D::Sprite>> sprites;
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