#pragma once
#include "TutorialEvent.h"

// �`���[�g���A���̐����̃}�l�[�W���[�N���X
class TutorialEventManager
{
private:
	// �R���X�g���N�^�Ȃǂ�private��
	TutorialEventManager() = default;
	~TutorialEventManager() = default;

	TutorialEvent tutorialEvent;
	bool isNext = false;

public:
	TutorialEventManager(const TutorialEventManager& obj) = delete;
	TutorialEventManager& operator=(const TutorialEventManager& obj) = delete;
	// �C���X�^���X�擾
	static TutorialEventManager* GetInstance();

	// ������
	void Initialize() { tutorialEvent.Initialize(); }
	// �X�V
	void Update();
	// �`��
	void Draw();
	// ���̃t�F�[�Y�֐i�߂�
	void NextPhase() { isNext = true; }
};