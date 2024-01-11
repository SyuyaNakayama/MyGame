#pragma once
#include <chrono>
#include <array>

namespace WristerEngine
{
	// �t���[���P�ʂł̃^�C�}�[
	class FrameTimer
	{
	private:
		int timer;
		int timeMem;

		/// <summary>
		/// �t���[������b�ɕϊ�
		/// </summary>
		/// <param name="fps">����FPS</param>
		/// <returns>[0]�ɕb�A[1]��999�ȉ��̃~���b������</returns>
		std::array<int, 2> ConvertToSecond(int time, int fps) const;

	public:
		// �R���X�g���N�^
		FrameTimer(int interval = 0) { timer = 0; timeMem = interval; }
		// �X�V
		bool Update();
		// �o�߃t���[�����擾
		int GetTime() const { return timer; }
		// �o�߃t���[����b�ɕϊ����Ď擾
		std::array<int, 2> GetTime(int fps) const { return ConvertToSecond(timer, fps); }
		// �o�߃t���[���𐳋K�����Ď擾
		float GetTimeRate() const { return (float)timer / (float)timeMem; }
		// �c��t���[�����擾
		int GetRemainTime() const { return timeMem - timer; }
		// �c��t���[����b�ɕϊ����Ď擾
		std::array<int, 2> GetRemainTime(int fps) const { return ConvertToSecond(GetRemainTime(), fps); }
		// �c��t���[���𐳋K�����Ď擾
		float GetRemainTimeRate() const { return (float)GetRemainTime() / (float)timeMem; }
		// ���b�v�t���[�����擾
		int GetInterval() const { return timeMem; }
	};

	// �������Ԃł̃^�C�}�[
	class RealTimer
	{
	private:
		std::chrono::steady_clock::time_point startTime;
		std::chrono::steady_clock::time_point nowTime;
		float timeMem;

	public:
		// �R���X�g���N�^
		RealTimer(float limitTime = 0) { timeMem = limitTime; startTime = std::chrono::steady_clock::now(); }
		// �X�V
		bool Update();
		// �v���J�n
		void Start() { startTime = std::chrono::steady_clock::now(); }
		// �o�ߎ��Ԃ��擾
		float GetTime() const;
		// �o�ߎ��Ԃ𐳋K�����Ď擾
		float GetTimeRate() const { return GetTime() / timeMem; }
		// �c�莞�Ԃ��擾
		float GetRemainTime() const { return timeMem - GetTime(); }
		// �c�莞�Ԃ𐳋K�����Ď擾
		float GetRemainTimeRate() const { return GetRemainTime() / timeMem; }
		// ���b�v���Ԃ��擾
		float GetInterval() const { return timeMem; }
	};
}