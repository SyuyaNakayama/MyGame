#pragma once
#include "Timer.h"

namespace WristerEngine
{
	// FPS�֘A����
	class FPS
	{
	private:
		std::chrono::steady_clock::time_point reference;
		float maxFPS = 60;
		int fps = 0;
		RealTimer oneSecond = 1.0f;
		FrameTimer oneSecondFrames = INT32_MAX;

		FPS() = default;
		~FPS() = default;

	public:
		FPS(const FPS& obj) = delete;
		FPS& operator=(const FPS& obj) = delete;

		// �C���X�^���X�擾
		static FPS* GetInstance();
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="maxfps">�ő�FPS�l</param>
		void Initialize(float maxfps);
		// FPS�Œ�
		void Fix();
		// FPS�擾
		int GetFPS() { return fps; }
		// �ő�FPS���擾
		int GetMaxFPS() { return (int)maxFPS; }
	};
}