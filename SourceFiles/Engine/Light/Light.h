#pragma once
#include "Vector.h"
#include "Color.h"
#include <cmath>

// ライト基底クラス
class BaseLight
{
private:
	ColorRGB lightcolor; // ライト色
	bool active = false; // 有効フラグ

public:
	// setter
	void SetLightColor(const ColorRGB& lightcolor_) { lightcolor = lightcolor_; }
	void SetActive(bool active_) { active = active_; }
	// getter
	ColorRGB GetLightColor() { return lightcolor; }
	bool IsActive() { return active; }
};

// 平行光源
class DirectionalLight : public BaseLight
{
private:
	Vector3 lightdir = { 1,0,0 }; // ライト光線方向

public:
	struct ConstBufferData
	{
		Vector3 lightv; // ライトへの方向を表すベクトル
		float pad;
		ColorRGB lightcolor; // ライトの色
		unsigned int active;
	};

	// ライト光線方向を変更
	void SetLightDir(const Vector3& lightdir_) { lightdir = Normalize(lightdir_); }
	// ライト光線方向を取得
	Vector3 GetLightDir() { return lightdir; }
};

// スポットライト
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

// 点光源
class PointLight : public BaseLight
{
private:
	Vector3 lightpos;
	Vector3 lightAtten = { 1,1,1 }; // ライト距離減衰係数

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