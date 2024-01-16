#pragma once
#include "Timer.h"

namespace WristerEngine
{
	// イージング
	class Easing
	{
	public:
		enum class Type
		{
			Sqrt,	// √x
			OutElastic, // https://easings.net/ja#easeOutElastic
			OutBounce, // https://easings.net/ja#easeOutBounce
		};

		// イージングの最大値
		static const float MAX;

	private:
		FrameTimer timer = 0; // タイマー
		float x = 0; // イージングの割合
		Type type;
		bool isFinish;

		// イージングの関数テーブル
		static float (Easing::* Ease[])();

		// √x
		float Sqrt() { return std::sqrtf(x); }
		// https://easings.net/ja#easeOutElastic
		float OutElastic();
		// https://easings.net/ja#easeOutBounce
		float OutBounce();

	public:
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="easeTime">イージングの時間</param>
		void Initialize(int easeTime, Type type_);

		/// <summary>
		/// 更新
		/// </summary>
		/// <returns>イージングの値(0~1)</returns>
		float Update();

		// リスタート
		void Restart() { timer = timer.GetInterval(); isFinish = false; }

		// 終了したか
		bool IsFinish() { return isFinish; }
	};

	// ループするイージング
	class LoopEasing
	{

	};
}