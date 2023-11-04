#pragma once

const float PI = 3.141592f; // 円周率
const float ONE_DEG_RAD = PI / 180.0f; // 1°のラジアン変換

// 角度
class Angle
{
	float angle;

	// 度数法をラジアンに変換
	float ToRadian(int deg) { return (float)deg * ONE_DEG_RAD; }

public:
	float operator+() const { return angle; }
	float operator-() const { return -angle; }
	void operator++(int) { angle += ONE_DEG_RAD; }
	void operator--(int) { angle -= ONE_DEG_RAD; }
	void operator+=(float rad) { angle += rad; }
	void operator+=(int deg) { angle += ToRadian(deg); }
	void operator-=(float rad) { angle -= rad; }
	void operator-=(int deg) { angle -= ToRadian(deg); }
	operator float() { return angle; }
	Angle(float rad) { angle = rad; } // ラジアン代入
	Angle(int deg) { angle = ToRadian(deg); } // 度数代入
};

// XYZ軸のenum class
enum class Axis { X, Y, Z };

// 数をループさせる関数
int NumberLoop(int num, int max, int min = 0);

/// <summary>
/// 半分の値を返す
/// </summary>
/// <typeparam name="T">型名</typeparam>
/// <param name="num">値</param>
/// <returns>num / 2の値</returns>
template<class T>
T Half(T num)
{
	return num / 2;
}