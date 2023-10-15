#pragma once
#include "Player.h"
#include "Block.h"
#include "SpawnObject.h"
#include "JsonLoader.h"
#include <chrono>

// �X�e�[�W�Ɋ֌W����I�u�W�F�N�g�S�ʂ̃N���X
class Stage
{
	static float STAGE_TIME;

	std::list<std::unique_ptr<GameObject>> gameObjects; // �v���C���[�A�ǁA���A�S�[���A��Q��
	LevelData* levelData = nullptr;
	static int score;
	RealTimer stageTime;
	bool isFinished;
	
public:
	// ������
	void Initialize();
	// �X�V
	void Update();
	/// <summary>
	/// �X�R�A���Z
	/// </summary>
	/// <param name="score_">���Z����X�R�A</param>
	static void AddScore(int score_) { score += score_; }
	// getter
	bool IsFinished() { return isFinished; }
	float GetRemainTime() { return stageTime.GetRemainTime(); }
	static int GetScore() { return score; }
	// �X�R�A���Z�b�g
	static void ResetScore() { score = 0; }
	// �^�C�����Z�b�g
	void ResetTime() { stageTime = STAGE_TIME; }
};