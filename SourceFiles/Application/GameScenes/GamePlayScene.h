#pragma once
#include "BaseScene.h"
#include "Stage.h"
#include "AudioManager.h"
#include "BitMapNumber.h"
#include "MathUtility.h"
#include "FPS.h"

// �X�^�[�g�O�̃J�E���g�_�E�����o
class StartCountDown
{
private:
	static const int COUNT_DOWN_TIME = 3;
	static int fps;
	BitMapNumber countUI;
	FrameTimer count = 0;

public:
	/// <summary>
	/// �C���X�^���X����
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static std::unique_ptr<StartCountDown> Create();
	// �X�V
	void Update();
	// �`��
	void Draw();
	// getter
	bool IsFinish() { return count.Update(); }
};

class UIDrawer : public AbstractUIDrawer
{
private:


public:
	// ������(�I�[�o�[���C�h)
	void Initialize();
	// �X�V(�I�[�o�[���C�h)
	void Update();
	// �`��(�I�[�o�[���C�h)
	void Draw();
};

// �Q�[���v���C�V�[���̏���
class GamePlayScene : public BaseScene
{
private:
	Stage stage;
	ViewProjection viewProjection;
	Audio* audio = nullptr;
	std::unique_ptr<Sprite> uiScore;
	std::unique_ptr<Sprite> uiClock;
	BitMapNumber scoreSprite;
	BitMapNumber timeIntSprite; // �c�莞�Ԑ�����
	BitMapNumber timeDecSprite; // �c�莞�ԏ�����
	Angle easingColor = 0; // ����UI�F�̃C�[�W���O�Ɏg��
	std::unique_ptr<StartCountDown> countDown;

	// ������(�I�[�o�[���C�h)
	void Initialize();
	// �X�V(�I�[�o�[���C�h)
	void Update();
	// �`��(�I�[�o�[���C�h)
	void Draw();

	// UI������
	void InitializeUI();
	// UI�X�V
	void UpdateUI();
};