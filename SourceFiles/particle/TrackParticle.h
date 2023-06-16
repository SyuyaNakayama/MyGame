#pragma once
#include "WorldTransform.h"
#include "Timer.h"
#include <list>

// �w�肵���I�u�W�F�N�g�ɒǔ�����p�[�e�B�N��
class TrackParticle
{
public:
	// �p�[�e�B�N��1��
	struct Particle
	{
		Vector3 parentPrePos; // �e���W
		Vector3 position{}; // ���W
		Vector3 velocity{}; // ���x
		Vector3 accel{}; // �����x
		Timer frame = 0;
		float scale = 1.0f; // �X�P�[��
		float s_scale = 1.0f; // �����l
		float e_scale = 0.0f;	// �ŏI�l
		WorldTransform* parent = nullptr;

		void Update();
	};

	struct AddProp
	{
		WorldTransform* parent = nullptr;
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