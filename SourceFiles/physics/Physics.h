#pragma once
#include "WorldTransform.h"

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

public:
	static void SetGravity(float g) { gravity = g; }
	void SetWorldTransform(WorldTransform* w) { worldTransform = w; }
	void SetMass(float m) { mass = m; }
	void SetForce(float f) { force = f; }
	void SetForceDir(Vector3 dir) { forceDir = dir; }
	void SetMu(float mu_) { mu = mu_; }
	void Update();
};