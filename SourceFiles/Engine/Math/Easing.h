#pragma once
#include "Timer.h"

namespace WristerEngine
{
	// �C�[�W���O
	class Easing
	{
	public:
		enum class Type
		{
			Sqrt,	// ��x
			OutElastic, // https://easings.net/ja#easeOutElastic
			OutBounce, // https://easings.net/ja#easeOutBounce
		};

		// �C�[�W���O�̍ő�l
		static const float MAX;

	private:
		FrameTimer timer = 0; // �^�C�}�[
		float x = 0; // �C�[�W���O�̊���
		Type type;
		bool isFinish;

		// �C�[�W���O�̊֐��e�[�u��
		static float (Easing::* Ease[])();

		// ��x
		float Sqrt() { return std::sqrtf(x); }
		// https://easings.net/ja#easeOutElastic
		float OutElastic();
		// https://easings.net/ja#easeOutBounce
		float OutBounce();

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
		void Restart() { timer = timer.GetInterval(); isFinish = false; }

		// �I��������
		bool IsFinish() { return isFinish; }
	};

	// ���[�v����C�[�W���O
	class LoopEasing
	{

	};
}