#pragma once
#include "ViewProjection.h"
#include "Quaternion.h"

// デバッグカメラ
class DebugCamera : public ViewProjection
{
private:
	float distance = 50;
	Quaternion rotQ = 1.0f;

public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="targetPos">注視点座標</param>
	/// <param name="distance">注視点座標までの距離</param>
	void Initialize(Vector3 targetPos = { 0,0,0 }, float distance = 50);
	// 更新
	void Update();
};