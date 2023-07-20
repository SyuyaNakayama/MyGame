#pragma once
#include "WorldTransform.h"
#include <memory>

// 物理計算
class Physics
{
private:
	static float gravity;
	static Vector3 gravityDir; // 重力の向き
	static float k_air; // 空気抵抗の比例定数
	WorldTransform* worldTransform = nullptr;
	Vector3 vel; // 速度
	float accel = 0; // 加速度
	float force = 0; // 力の大きさ
	Vector3 forceDir; // 力の向き
	float mass = 1;  // 質量
	float mu = 0.1f; // 摩擦係数
	bool isCollided = false; // 衝突処理を行ったか
	bool isFreeFall = false; // 自由落下フラグ
	float fallSpd = 0; // 落下速度

public:
	static std::unique_ptr<Physics> Create(WorldTransform* w);
	static void SetGravity(float g) { gravity = g; }
	void Update();
	Vector3 SetVelocity(Vector3 velocity) { return vel = velocity; }
	void SetForce(float f) { force = f; }
	void SetForceDir(Vector3 dir) { forceDir = Normalize(dir); } // dirは自動的に正規化される
	void SetMass(float m) { mass = m; }
	void SetMu(float mu_) { mu = mu_; }
	void SetIsFreeFall(bool isFreeFall_) { isFreeFall = isFreeFall_; }
	Vector3 GetVelocity() { return vel; }
	float GetForce() { return accel * mass; }
	float GetMass() { return mass; }
	float GetMomentum() { return mass * vel.Length(); } // 運動量を取得
	void SetIsCollided(bool isCollided_) { isCollided = isCollided_; }
	bool IsCollided() { return isCollided; }
};