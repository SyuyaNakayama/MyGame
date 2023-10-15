#pragma once
#include "BaseCamera.h"

// 後で処理を修正するための参考資料
// https://docs.google.com/presentation/d/1XNAtNpD0L91TbVdtewIjw1vmtithvjUjOqEj-8s6TSE/edit#slide=id.g22dd4f4a57f_0_213

// プレイヤーに追従するカメラ
class PlayerCamera : public BaseCamera
{
	Vector3 parentPrePos;
	
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="parent">ワールドトランスフォームの親ポインタ</param>
	void Initialize(WorldTransform* parent);
	// 更新
	void Update();
};