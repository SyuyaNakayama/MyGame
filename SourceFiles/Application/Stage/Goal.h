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

class Goal;

// �S�[���̋��ʕ������Ǘ�
class GoalManager final
{
private:
	Scene nowScene = Scene::Null;
	WristerEngine::Constant* constant = WristerEngine::Constant::GetInstance();
	WristerEngine::FrameTimer scoreChangeTimer = 600;
	bool isScoreChange = false;
	WristerEngine::Roulette roulette;
	TutorialEvent* tutorialEvent = TutorialEvent::GetInstance();
	const std::vector<UINT32>* tutorialEventPhase = nullptr;
	UINT32 phase = 0;
	std::vector<Goal*> goals;
	WristerEngine::LoopEasing goalColor;
	bool preTutorialEnd = false; // �O�t���[���̃`���[�g���A���I���t���O

	GoalManager() = default;
	~GoalManager() = default;
	// �`���[�g���A���ł͂Ȃ������擾
	bool IsNotTutorial() const { return nowScene != Scene::Tutorial || tutorialEvent->IsEnd(); }

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

	// �C���X�^���X�擾
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

	// �`���[�g���A���̐�����i�߂�
	void NextPhase() { tutorialEvent->NextPhase(); }
	// �S�[���I�u�W�F�N�g�̃|�C���^��ǉ�
	void AddGoalPointer(Goal* pGoal) { goals.push_back(pGoal); }
	// �S�[���I�u�W�F�N�g�̃|�C���^������
	void ResetGoalPointer() { goals.clear(); }
};

// �S�[���̃I�u�W�F�N�g
class Goal : public WristerEngine::BoxCollider, public WristerEngine::_3D::GameObject
{
	friend GoalManager;

	GoalManager* manager = GoalManager::GetInstance();
	WristerEngine::_3D::Object3d* object = nullptr;
	Vector3 normal;
	Score score = Score::_10;
	WristerEngine::ColorRGBA initColor;

	/// <summary>
	/// �X�R�A�ύX����
	/// </summary>
	/// <param name="nextScore">���̃X�R�A</param>
	void ChangeScore(Score nextScore);

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="objectData">Json�t�@�C������ǂݍ��񂾃f�[�^</param>
	void Initialize(const ObjectData& objectData);
	// �X�V
	void Update(){}
	// �Փ˃R�[���o�b�N�֐�(BoxCollider��)
	void OnCollision(BoxCollider* collider);

	/// <summary>
	/// �F��ς���
	/// </summary>
	/// <param name="colorRate">���x</param>
	void ChangeColor(float colorRate);
};