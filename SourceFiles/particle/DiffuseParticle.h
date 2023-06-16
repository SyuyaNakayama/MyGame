#pragma once
#include "Timer.h"
#include <list>
#include "Vector.h"

// �g�U����p�[�e�B�N��(���܂ł̂��)
class DiffuseParticle
{
public:
	// �p�[�e�B�N��1��
	struct Particle
	{
		Vector3 position{}; // ���W
		Vector3 velocity{}; // ���x
		Vector3 accel{}; // �����x
		Timer frame = 0;
		float scale = 1.0f; // �X�P�[��
		float s_scale = 1.0f; // �����l
		float e_scale = 0.0f;	// �ŏI�l

		void Update();
	};

	struct AddProp
	{
		Vector3 posOffset;
		Vector3 velOffset;
		Vector3 accOffset;
		float posRange = 1.0f;
		float velRange = 0.1f;
		float accRange = 0.001f;
		int lifeTime = 60;
		float start_scale = 1.0f;
		float end_scale = 0.0f;
		unsigned short addNum = 1;
	};

private:
	std::list<Particle> particles;

public:
	void Update();
	void Clear() { particles.clear(); }
	void Add(const AddProp& particleProp);
	const std::list<Particle>& GetParticles() const { return particles; }
};