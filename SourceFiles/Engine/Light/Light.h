#pragma once
#include "Vector.h"
#include "Color.h"
#include <cmath>

namespace WristerEngine
{
	// ���C�g���N���X
	class BaseLight
	{
	private:
		ColorRGB color; // ���C�g�F
		bool active = false; // �L���t���O

	public:
		// setter
		void SetColor(const ColorRGB& color_) { color = color_; }
		void SetActive(bool active_) { active = active_; }
		// getter
		const ColorRGB& GetColor()  { return color; }
		bool IsActive() const { return active; }
	};

	// ���s����
	class DirectionalLight : public BaseLight
	{
	private:
		Vector3 dir = { 1,0,0 }; // ���C�g��������

	public:
		struct ConstBufferData
		{
			Vector3 lightv; // ���C�g�ւ̕�����\���x�N�g��
			float pad;
			ColorRGB lightcolor; // ���C�g�̐F
			unsigned int active;
		};

		// ���C�g����������ύX
		void SetDir(const Vector3& lightdir_) { dir = Normalize(lightdir_); }
		// ���C�g�����������擾
		const Vector3& GetDir()  { return dir; }
	};

	// �X�|�b�g���C�g
	class SpotLight : public BaseLight
	{
	private:
		Vector3 dir;
		Vector3 pos;
		Vector3 atten = { 1,1,1 };
		Vector2 factorAngleCos = { 0.5f,0.2f };

	public:
		struct ConstBufferData
		{
			Vector3 lightv;
			float pad1;
			Vector3 lightpos;
			float pad2;
			ColorRGB lightcolor;
			float pad3;
			Vector3 lightatten;
			float pad4;
			Vector2 lightfactoranglecos;
			unsigned int active;
			float pad5;
		};

		// setter
		void SetDir(const Vector3& dir_) { dir = Normalize(dir_); }
		void SetPos(const Vector3& pos_) { pos = pos_; }
		void SetAtten(const Vector3& atten_) { atten = atten_; }
		void SetFactorAngle(const Vector2& factorAngle)
		{
			factorAngleCos.x = std::cos(factorAngle.x);
			factorAngleCos.y = std::cos(factorAngle.y);
		}
		// getter
		const Vector3& GetDir() { return dir; }
		const Vector3& GetPos() { return pos; }
		const Vector3& GetAtten() { return atten; }
		const Vector2& GetFactorAngleCos() { return factorAngleCos; }
	};

	// �_����
	class PointLight : public BaseLight
	{
	private:
		Vector3 pos;
		Vector3 atten = { 1,1,1 }; // ���C�g���������W��

	public:
		struct ConstBufferData
		{
			Vector3 lightpos;
			float pad1;
			ColorRGB lightcolor;
			float pad2;
			Vector3 lightAtten;
			unsigned int active;
		};

		// setter
		void SetPos(const Vector3& pos_) { pos = pos_; }
		void SetAtten(const Vector3& atten_) { atten = atten_; }
		// getter
		const Vector3& GetPos() { return pos; }
		const Vector3& GetAtten() { return atten; }
	};
}