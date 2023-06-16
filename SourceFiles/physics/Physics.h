#pragma once
#include "Vector.h"
#include "Collider.h"

enum class Primitive { Box, Sphere };

// •¨—ŒvŽZ
class Physics : public virtual BaseCollider
{
protected:
	static float gravity;
	Vector3 vel; // ‘¬“x
	float accel = 0; // ‰Á‘¬“x
	float force = 0; // —Í‚Ì‘å‚«‚³
	Vector3 forceDir; // —Í‚ÌŒü‚«
	float mass = 1;  // Ž¿—Ê
	float mu = 0.1f; // –€ŽCŒW”
	float rebE = 1.0f; // ”½”­ŒW” -> rebound e

public:
	Physics();
	virtual ~Physics() = default;
	void Update();
	virtual void OnCollision(Physics* physics);
};