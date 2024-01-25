#pragma once
#include "Timer.h"

namespace WristerEngine
{
	const int MAX_FPS = 60;

	// FPS�֘A����
	class FPS final
	{
	private:
		std::chrono::steady_clock::time_point reference;
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
		void Initialize();
		// FPS�Œ�
		void Fix();
		// FPS�擾
		int GetFPS() const { return fps; }
	};
}