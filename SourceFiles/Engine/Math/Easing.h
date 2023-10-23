#pragma once
#include "Timer.h"

// �C�[�W���O
class Easing
{
public:
	enum class Type
	{
		Sqrt,	// ��x
	};

private:
	FrameTimer easeRate = 0; // �C�[�W���O�̊���
	Type type;
	bool isFinish;

	// �C�[�W���O�̊֐��e�[�u��
	static float (Easing::*Ease[])();
	
	// ��x
	float Sqrt() { return std::sqrtf((float)easeRate.GetTimeRate()); }

public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="easeTime">�C�[�W���O�̎���</param>
	void Initialize(int easeTime, Type type_);

	/// <summary>
	/// �X�V
	/// </summary>
	/// <returns>�C�[�W���O�̒l(0~1)</returns>
	float Update();

	// ���X�^�[�g
	void Restart() { easeRate = easeRate.GetInterval(); isFinish = false; }
};