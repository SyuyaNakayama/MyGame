#pragma once
#include "Timer.h"
#include <list>
#include "Vector.h"

// �n�_����I�_�֌������p�[�e�B�N��
class DirectionalParticle
{
public:
	// �p�[�e�B�N��1��
	struct Particle
	{
		Vector3 start; // �n�_
		Vector3 end; // �I�_
		Vector3 position;
		float scale = 1;
		unsigned short splitNum = 1;
		float angle = 0;
		float radius = 0;
		Timer frame;
		std::vector<Vector3> controlPoints; // ����_

		void ComputeControlPoints();
		void Update();
	};

	struct AddProp
	{
		Vector3 start;
		Vector3 end;
		float scale = 1;
		unsigned short splitNum = 1; // ����_�̐�
		float angle = 0; // {0,1,0}��0���W�A��
		float radius = 0;
		int lifeTime = 60;
	};

private:
	std::list<Particle> particles;

public:
	void Update();
	void Clear() { particles.clear(); }
	void Add(const AddProp& particleProp);
	const std::list<Particle>& GetParticles() const { return particles; }
};