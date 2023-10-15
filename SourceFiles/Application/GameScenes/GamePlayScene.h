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
	const float COUNT_DOWN_TIME = 3.0f;
	BitMapNumber countUI;
	RealTimer count = COUNT_DOWN_TIME;

public:
	static std::unique_ptr<StartCountDown> Create();
	void Update();
	void Draw();
	bool IsFinish() { return count.Update(); }
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
	BitMapNumber timeIntSprite2; // �c�莞�Ԑ�����
	BitMapNumber timeDecSprite2; // �c�莞�ԏ�����
	Angle easingColor = 0; // ����UI�F�̃C�[�W���O�Ɏg��
	std::unique_ptr<StartCountDown> countDown;
	FPS* fps = FPS::GetInstance();
	FrameTimer timer = 20 * 60;

	void Initialize();
	void Update();
	void Draw();

	void UIInitialize();
	void UIUpdate();
};