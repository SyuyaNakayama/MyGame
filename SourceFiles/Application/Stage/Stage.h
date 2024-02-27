#pragma once
#include "Block.h"
#include "JsonLoader.h"
#include "Player.h"
#include "SpawnObject.h"
#include <chrono>

// �X�e�[�W�Ɋ֌W����I�u�W�F�N�g�S�ʂ̃N���X
class Stage
{
	static const int STAGE_TIME = 60;

	std::list<std::unique_ptr<WristerEngine::_3D::GameObject>> gameObjects; // �v���C���[�A�ǁA���A�S�[���A��Q��
	WristerEngine::LevelData* levelData = nullptr;
	static int score;
	WristerEngine::FrameTimer stageTime;
	bool isFinished;
	int fps = 0; // �擾����FPS

public:
	static float GROUND_POS_Y;

	// ������
	void Initialize();
	// �X�V
	void Update();
	/// <summary>
	/// �X�R�A���Z(0�����ɂ͂Ȃ�Ȃ�)
	/// </summary>
	/// <param name="score_">���Z����X�R�A</param>
	static void AddScore(int score_) { score = max(score + score_, 0); }
	// getter
	bool IsFinished() { return isFinished; }
	/// <summary>
	/// �c�莞�Ԃ��擾
	/// </summary>
	/// <returns>[0]�ɕb�A[1]��999�ȉ��̃~���b������</returns>
	std::array<int, 2> GetRemainTime();
	static int GetScore() { return score; }
	// �X�R�A���Z�b�g
	static void ResetScore() { score = 0; }
	// �^�C�����Z�b�g
	void ResetTime() { stageTime = STAGE_TIME * fps; }
	// �I��
	void Finalize() { gameObjects.clear(); }
};