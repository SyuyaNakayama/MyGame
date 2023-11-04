#pragma once

const float PI = 3.141592f; // �~����
const float ONE_DEG_RAD = PI / 180.0f; // 1���̃��W�A���ϊ�

// �p�x
class Angle
{
	float angle;

	// �x���@�����W�A���ɕϊ�
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
	Angle(float rad) { angle = rad; } // ���W�A�����
	Angle(int deg) { angle = ToRadian(deg); } // �x�����
};

// XYZ����enum class
enum class Axis { X, Y, Z };

// �������[�v������֐�
int NumberLoop(int num, int max, int min = 0);

/// <summary>
/// �����̒l��Ԃ�
/// </summary>
/// <typeparam name="T">�^��</typeparam>
/// <param name="num">�l</param>
/// <returns>num / 2�̒l</returns>
template<class T>
T Half(T num)
{
	return num / 2;
}