#pragma once
#include "Collider.h"
#include "GameObject.h"
#include "Random.h"

// ���ƕǂ̃I�u�W�F�N�g
class Block : public WristerEngine::BoxCollider, public WristerEngine::_3D::GameObject
{
	WristerEngine::_3D::Object3d* object;
	Vector3 normal;

public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="objectData">Json�t�@�C������ǂݍ��񂾃f�[�^</param>
	void Initialize(const WristerEngine::ObjectData& objectData);
	// �X�V
	void Update() {}
	// �Փ˃R�[���o�b�N�֐�(BoxCollider��)
	void OnCollision(BoxCollider* collider);
};

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

	WristerEngine::_3D::Object3d* object;
	Vector3 normal;
	Score score;
	WristerEngine::ColorRGBA initColor;

	void ChangeScore();

public:
	// �ÓI������
	static void StaticInitialize() { scoreChangeTimer = 600; }
	// �ÓI�X�V
	static void StaticUpdate();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="objectData">Json�t�@�C������ǂݍ��񂾃f�[�^</param>
	void Initialize(const WristerEngine::ObjectData& objectData);
	// �X�V
	void Update();
	// �Փ˃R�[���o�b�N�֐�(BoxCollider��)
	void OnCollision(BoxCollider* collider);
};