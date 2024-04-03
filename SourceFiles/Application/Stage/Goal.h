#pragma once
#include "Collider.h"
#include "GameObject.h"
#include "Random.h"
#include "TutorialEvent.h"

// �S�[���̃I�u�W�F�N�g
class Goal : public WristerEngine::BoxCollider, public WristerEngine::_3D::GameObject
{
	enum class Score
	{
		_M10 = -10,
		_10 = 10,
		_20 = 20,
		_30 = 30,
		_50 = 50,
	};

	static std::map<Score, std::string> SCORE_TEX_NAME;
	static const std::vector<Score> SCORE_TABLE;
	static WristerEngine::FrameTimer scoreChangeTimer;
	static bool isScoreChange;
	static WristerEngine::Random_Int randScore;
	static WristerEngine::Roulette roulette;
	static TutorialEvent* tutorialEvent;
	static const std::vector<UINT32>* tutorialEventPhase;
	static UINT32 phase;

	WristerEngine::_3D::Object3d* object = nullptr;
	Vector3 normal;
	Score score = Score::_10;
	WristerEngine::ColorRGBA initColor;

	void ChangeScore();

public:
	// �ÓI������
	static void StaticInitialize();
	// �ÓI�X�V
	static void StaticUpdate();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="objectData">Json�t�@�C������ǂݍ��񂾃f�[�^</param>
	void Initialize(const ObjectData& objectData);
	// �X�V
	void Update();
	// �Փ˃R�[���o�b�N�֐�(BoxCollider��)
	void OnCollision(BoxCollider* collider);
};