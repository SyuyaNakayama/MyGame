#pragma once
#include "Timer.h"

namespace WristerEngine
{
	// �C�[�W���O
	// �Q�l : https://easings.net/ja#
	class Easing
	{
	public:
		enum class Type
		{
			Sqrt, // ��x
			OutElastic,
			OutBounce,
			EaseInOutBack,
			EaseOutQuint,
			EaseInOutQuint,
		};

		// �C�[�W���O�̍ő�l
		static const float MAX;

	private:
		FrameTimer timer = 0; // �^�C�}�[
		float x = 0; // �C�[�W���O�̊���
		Type type = Type::Sqrt;
		bool isFinish = false;

		// �C�[�W���O�̊֐��e�[�u��
		static float (Easing::* Ease[])();

		// ��x
		float Sqrt() { return std::sqrtf(x); }
		// https://easings.net/ja#easeOutElastic
		float OutElastic();
		// https://easings.net/ja#easeOutBounce
		float OutBounce();
		// https://easings.net/ja#easeInOutBack
		float EaseInOutBack();
		// https://easings.net/ja#easeOutQuint
		float EaseOutQuint() { return 1 - powf(1 - x, 5); }
		// https://easings.net/ja#easeInOutQuint
		float EaseInOutQuint();

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
		bool IsFinish() const { return isFinish; }
	};

	// ���[�v����C�[�W���O
	class LoopEasing
	{
	public:
		enum class Type
		{
			Cos,	// cos(x)
		};

	private:
		FrameTimer timer = 0; // �^�C�}�[
		float x = 0; // �C�[�W���O�̊���
		Type type;

		// �C�[�W���O�̊֐��e�[�u��
		static float (LoopEasing::* Ease[])();

		// ��x
		float Cos();

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
		void Restart() { timer = timer.GetInterval(); }

	};
}