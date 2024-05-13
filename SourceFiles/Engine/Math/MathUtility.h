#pragma once
#include <vector>

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
template <class T>
T NumberLoop(T num, T max, T min = 0)
{
	if (num > max) { return num - max + min; }
	if (num < min) { return max - min + num; }
	return num;
}

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

/// <summary>
/// �����l��r
/// </summary>
/// <typeparam name="T">�ϐ��^</typeparam>
/// <param name="n">�l</param>
/// <param name="list">��r����l�̔z��</param>
/// <returns>list��n�Ɠ��l����������true</returns>
template<class T>
bool IsAny(T n, std::vector<T> list)
{
	bool flag = false;
	for (T num : list)
	{
		if (n == num) { flag = true; }
	}
	return flag;
}