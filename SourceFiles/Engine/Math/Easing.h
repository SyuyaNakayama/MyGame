#pragma once
#include "Timer.h"

// イージング
class Easing
{
public:
	enum class Type
	{
		Sqrt,	// √x
	};

private:
	FrameTimer easeRate = 0; // イージングの割合
	Type type;
	bool isFinish;

	// イージングの関数テーブル
	static float (Easing::*Ease[])();
	
	// √x
	float Sqrt() { return std::sqrtf((float)easeRate.GetTimeRate()); }

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
	void Restart() { easeRate = easeRate.GetInterval(); isFinish = false; }
};