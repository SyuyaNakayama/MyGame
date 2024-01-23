#pragma once
#include "AudioManager.h"
#include "BaseScene.h"
#include "BitMapNumber.h"
#include "Easing.h"
#include "FPS.h"
#include "MathUtility.h"
#include "Stage.h"

// �X�^�[�g�O�̃J�E���g�_�E�����o
class StartCountDown
{
private:
	static const int COUNT_DOWN_TIME = 3;
	static int fps;
	WristerEngine::_2D::BitMapNumber countUI;
	WristerEngine::FrameTimer countTimer = 0;

public:
	/// <summary>
	/// �C���X�^���X����
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static std::unique_ptr<StartCountDown> Create();
	/// <summary>
	/// �X�V
	/// </summary>
	/// <returns>�J�E���g�_�E�����I��������̃t���O</returns>
	bool Update();
	// �`��
	void Draw();
	// FPS���擾
	static int GetFPS() { return fps; }
};

// UI�`��N���X(�Q�[���V�[���p)
class UIDrawerGameScene : public WristerEngine::_2D::AbstractUIDrawer
{
private:
	const float SLIDE_DIS_UI_GO = 500; // "Go!"��UI���X���C�h���鋗��

	Stage* stage;
	std::unique_ptr<WristerEngine::_2D::Sprite> uiScore;
	std::unique_ptr<WristerEngine::_2D::Sprite> uiClock;
	WristerEngine::_2D::BitMapNumber scoreSprite;
	WristerEngine::_2D::BitMapNumber timeIntSprite; // �c�莞�Ԑ�����
	WristerEngine::_2D::BitMapNumber timeDecSprite; // �c�莞�ԏ�����
	Angle easingColor = 0; // ����UI�F�̃C�[�W���O�Ɏg��
	std::unique_ptr<StartCountDown> countDown;
	std::unique_ptr<WristerEngine::_2D::Sprite> uiGo;
	Vector2 uiGoSize;
	WristerEngine::Easing uiGoEasing;
	std::map<std::string, std::unique_ptr<WristerEngine::_2D::Sprite>> operateUI;
	std::map<WristerEngine::Key, std::unique_ptr<WristerEngine::_2D::Sprite>> keyUI;
	std::unique_ptr<WristerEngine::_2D::Sprite> frame;

	// "Go!"�̃A�j���[�V�����̊֐��|�C���^
	void (UIDrawerGameScene::* UIGoAnimation)() = nullptr;
	// �X���C�h
	void UIGoSlide();
	// �ҋ@
	void UIGoIdle();
	// �Y�[��
	void UIGoZoom();

public:
	// �R���X�g���N�^
	UIDrawerGameScene(Stage* stage_) { stage = stage_; }
	// ������(�I�[�o�[���C�h)
	void Initialize();
	// �X�V(�I�[�o�[���C�h)
	void Update();
	// �`��(�I�[�o�[���C�h)
	void Draw();
	// �J�E���g�_�E������
	bool IsCountDown() { return countDown.get() != nullptr; }
};

// �Q�[���v���C�V�[���̏���
class GamePlayScene : public WristerEngine::BaseScene
{
private:
	Stage stage;
	WristerEngine::_3D::ViewProjection viewProjection;
	WristerEngine::Audio* audio = nullptr;

	// ������(�I�[�o�[���C�h)
	void Initialize();
	// �X�V(�I�[�o�[���C�h)
	void Update();
	// �I��
	void Finalize() { stage.Finalize(); }
};