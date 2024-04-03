#pragma once
#include "Collider.h"
#include "GameObject.h"
#include "Random.h"
#include "TutorialEvent.h"

enum class Score
{
	_M10 = -10,
	_10 = 10,
	_20 = 20,
	_30 = 30,
	_50 = 50,
};

// �S�[���̋��ʕ������Ǘ�
class GoalManager final
{
private:
	WristerEngine::FrameTimer scoreChangeTimer = 600;
	bool isScoreChange = false;
	WristerEngine::Roulette roulette;
	TutorialEvent* tutorialEvent = TutorialEvent::GetInstance();
	const std::vector<UINT32>* tutorialEventPhase = nullptr;
	UINT32 phase = 0;

	GoalManager() = default;
	~GoalManager() = default;

public:
	std::map<Score, std::string> SCORE_TEX_NAME =
	{
		{ Score::_M10,"Textures/score-10.png" },
		{ Score::_10, "Textures/score10.png" },
		{ Score::_20, "Textures/score20.png" },
		{ Score::_30, "Textures/score30.png" },
		{ Score::_50, "Textures/score50.png" }
	};
	
	GoalManager(const GoalManager& obj) = delete;
	GoalManager& operator=(const GoalManager& obj) = delete;

	static GoalManager* GetInstance();
	// ������
	void Initialize();
	// �X�V
	void Update();

	/// <summary>
	/// �X�R�A���擾
	/// </summary>
	/// <returns>���̃X�R�A</returns>
	Score GetScore() const;

	/// <summary>
	/// isScoreChange���擾
	/// </summary>
	/// <returns>isScoreChange</returns>
	bool IsScoreChange() const { return isScoreChange; }

	int GetChangeRemainTime() const { return scoreChangeTimer.GetRemainTime(); }

	UINT32 GetPhase() const { return phase; }
	const std::vector<UINT32>* GetTutorialEventPhase() const { return tutorialEventPhase; }

	bool IsTutorialEnd() const { return tutorialEvent->IsEnd(); }

	void NextPhase() { tutorialEvent->NextPhase(); }
};

// �S�[���̃I�u�W�F�N�g
class Goal : public WristerEngine::BoxCollider, public WristerEngine::_3D::GameObject
{
	GoalManager* manager = GoalManager::GetInstance();
	WristerEngine::_3D::Object3d* object = nullptr;
	Vector3 normal;
	Score score = Score::_10;
	WristerEngine::ColorRGBA initColor;

	// �X�R�A�ύX����
	void ChangeScore();

public:
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