#pragma once
#include "WorldTransform.h"
#include <memory>
#include <array>

// 物理計算
class Physics
{
private:
	static std::vector<std::array<Physics*, 2>> collideList;
	static float gravity; // 重力加速度
	static Vector3 gravityDir; // 重力の向き
	static float k_air; // 空気抵抗の比例定数
	WorldTransform* worldTransform = nullptr;
	Vector3 vel; // 速度
	float accel = 0; // 加速度
	float force = 0; // 力の大きさ
	Vector3 forceDir; // 力の向き
	float mass = 1;  // 質量
	float mu = 0.1f; // 摩擦係数
	bool isFreeFall = false; // 自由落下フラグ
	float fallSpd = 0; // 落下速度

public:
	/// <summary>
	/// インスタンス生成
	/// </summary>
	/// <param name="w">ワールドトランスフォーム</param>
	/// <returns>インスタンス</returns>
	static std::unique_ptr<Physics> Create(WorldTransform* w);
	// 動く物体と動かない物体の反発後の速度を計算
	void Backlash(const Vector3& wallNormal, float e); 
	// 動く2物体の反発後の速度を計算
	static void Backlash(Physics* p1, Physics* p2, float e); 
	// 重力加速度を設定
	static void SetGravity(float g) { gravity = g; }
	// 衝突処理実行判定をリセット
	static void ResetCollideList() { collideList.clear(); } 
	// 更新
	void Update();
	// setter
	Vector3 SetVelocity(Vector3 velocity) { return vel = velocity; }
	void SetForce(float f) { force = f; }
	void SetForceDir(Vector3 dir) { forceDir = Normalize(dir); } // dirは自動的に正規化される
	void SetMass(float m);
	void SetMu(float mu_) { mu = mu_; }
	void SetIsFreeFall(bool isFreeFall_) { isFreeFall = isFreeFall_; }
	// getter
	Vector3 GetVelocity() { return vel; }
	float GetForce() { return accel * mass; }
	float GetMass() { return mass; }
	WorldTransform* GetWorldTransform() { return worldTransform; }
	bool IsFreeFall() { return isFreeFall; }
	float GetMomentum() { return mass * vel.Length(); } // 運動量を取得
};