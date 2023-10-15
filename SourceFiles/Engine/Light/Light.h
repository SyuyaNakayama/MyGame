#pragma once
#include "Vector.h"
#include "Color.h"
#include <cmath>

// ���C�g���N���X
class BaseLight
{
private:
	ColorRGB lightcolor; // ���C�g�F
	bool active = false; // �L���t���O

public:
	// setter
	void SetLightColor(const ColorRGB& lightcolor_) { lightcolor = lightcolor_; }
	void SetActive(bool active_) { active = active_; }
	// getter
	ColorRGB GetLightColor() { return lightcolor; }
	bool IsActive() { return active; }
};

// ���s����
class DirectionalLight : public BaseLight
{
private:
	Vector3 lightdir = { 1,0,0 }; // ���C�g��������

public:
	struct ConstBufferData
	{
		Vector3 lightv; // ���C�g�ւ̕�����\���x�N�g��
		float pad;
		ColorRGB lightcolor; // ���C�g�̐F
		unsigned int active;
	};

	// ���C�g����������ύX
	void SetLightDir(const Vector3& lightdir_) { lightdir = Normalize(lightdir_); }
	// ���C�g�����������擾
	Vector3 GetLightDir() { return lightdir; }
};

// �X�|�b�g���C�g
class SpotLight : public BaseLight
{
private:
	Vector3 lightdir;
	Vector3 lightpos;
	Vector3 lightAtten = { 1,1,1 };
	Vector2 lightFactorAngleCos = { 0.5f,0.2f };

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
	void SetLightDir(const Vector3& lightdir_) { lightdir = Normalize(lightdir_); }
	void SetLightPos(const Vector3& lightpos_) { lightpos = lightpos_; }
	void SetLightAtten(const Vector3& lightAtten_) { lightAtten = lightAtten_; }
	void SetLightFactorAngle(const Vector2& lightFactorAngle)
	{
		lightFactorAngleCos.x = std::cos(lightFactorAngle.x);
		lightFactorAngleCos.y = std::cos(lightFactorAngle.y);
	}
	// getter
	const Vector3& GetLightDir() { return lightdir; }
	const Vector3& GetLightPos() { return lightpos; }
	const Vector3& GetLightAtten() { return lightAtten; }
	const Vector2& GetLightFactorAngleCos() { return lightFactorAngleCos; }
};

// �_����
class PointLight : public BaseLight
{
private:
	Vector3 lightpos;
	Vector3 lightAtten = { 1,1,1 }; // ���C�g���������W��

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
	void SetLightPos(const Vector3& lightpos_) { lightpos = lightpos_; }
	void SetLightAtten(const Vector3& lightAtten_) { lightAtten = lightAtten_; }
	// getter
	const Vector3& GetLightPos() { return lightpos; }
	const Vector3& GetLightAtten() { return lightAtten; }
};