#pragma once
#include "JsonLoader.h"

// �Q�[���ɕ\������Ă���I�u�W�F�N�g�̊��N���X
class GameObject
{
public:
	// ���z�f�X�g���N�^
	virtual ~GameObject() = default;
	/// <summary>
	/// ������(�������z�֐�)
	/// </summary>
	/// <param name="objectData">Json�t�@�C������ǂݍ��񂾃f�[�^</param>
	virtual void Initialize(const ObjectData& objectData) = 0;
	// �X�V(�������z�֐�)
	virtual void Update() = 0;
};