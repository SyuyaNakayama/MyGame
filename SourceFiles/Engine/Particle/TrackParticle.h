#pragma once
#include "Transform.h"
#include "Timer.h"
#include <list>

namespace WristerEngine
{
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
			FrameTimer frame = 0;
			float scale = 1.0f; // �X�P�[��
			float s_scale = 1.0f; // �����l
			float e_scale = 0.0f;	// �ŏI�l
			_3D::Transform* parent = nullptr;

			void Update();
		};

		struct AddProp
		{
			_3D::Transform* parent = nullptr;
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
		// �X�V
		void Update();
		// �p�[�e�B�N���폜
		void Clear() { particles.clear(); }
		// �p�[�e�B�N���ǉ�
		void Add(const AddProp& particleProp);
		// �p�[�e�B�N�����X�g�擾
		const std::list<Particle>& GetParticles() const { return particles; }
	};
}