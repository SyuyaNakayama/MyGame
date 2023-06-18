#pragma once
#include "WorldTransform.h"
#include <memory>

// •¨—ŒvZ
class Physics
{
private:
	static float gravity;
	WorldTransform* worldTransform = nullptr;
	Vector3 vel; // ‘¬“x
	float accel = 0; // ‰Á‘¬“x
	float force = 0; // —Í‚Ì‘å‚«‚³
	Vector3 forceDir; // —Í‚ÌŒü‚«
	float mass = 1;  // ¿—Ê
	float mu = 0.1f; // –€CŒW”
	bool isCollided = false; // Õ“Ëˆ—‚ğs‚Á‚½‚©

public:
	static void SetGravity(float g) { gravity = g; }
	static std::unique_ptr<Physics> Create(WorldTransform* w);
	void Update();
	Vector3 SetVelocity(Vector3 velocity) { return vel = velocity; }
	void SetForce(float f) { force = f; }
	void SetForceDir(Vector3 dir) { forceDir = Normalize(dir); } // dir‚Í©“®“I‚É³‹K‰»‚³‚ê‚é
	void SetMass(float m) { mass = m; }
	void SetMu(float mu_) { mu = mu_; }
	Vector3 GetVelocity() { return vel; }
	float GetForce() { return accel * mass; }
	float GetMass() { return mass; }
	float GetMomentum() { return mass * vel.Length(); } // ‰^“®—Ê‚ğæ“¾
	void SetIsCollided(bool isCollided_) { isCollided = isCollided_; }
	bool IsCollided() { return isCollided; }
};