#pragma once
#include "Matrix4.h"

class Quaternion
{
public:
	float x = 0, y = 0, z = 0, // ����
		w = 0; // ����

	Quaternion(float w_, Vector3 iv) { x = iv.x, y = iv.y, z = iv.z, w = w_; }
	Quaternion(float w_ = 0, float x_ = 0, float y_ = 0, float z_ = 0) { x = x_, y = y_, z = z_; w = w_; }
	Vector3 GetImaginary() const { return { x,y,z }; }
	Quaternion operator-()const { return { -w,x,y,z }; }
	// ������Z�q�I�[�o�[���[�h
	void operator*=(const Quaternion& q);
	void operator/=(float norm) { x /= norm, y /= norm, z /= norm, w /= norm; }
	// �����ɂ���
	void Conjugate() { x = -x, y = -y, z = -z; }
	// ����Quaternion��Norm��Ԃ�
	float Norm() const;
	// ���K������
	void Normalize() { *this /= Norm(); }
	// �tQuaternion�ɂ���
	void Inverse();
	// ��]�s������߂�
	Matrix4 MakeRotateMatrix() const;

	// �ÓI�֐�
	// �����o�ϐ��̒l��ς������Ȃ����͂��������g��
	// �P��Quaternion
	static Quaternion Identity() { return Quaternion(1, 0, 0, 0); }
	static Quaternion Conjugate(const Quaternion& q) { return Quaternion(q.w, -q.GetImaginary()); }
	static float Norm(const Quaternion& q) { return q.Norm(); }
	static Quaternion Normalize(const Quaternion& q);
	static Quaternion Inverse(const Quaternion& q);

	// �C�ӎ���]��Quaternion����(axis�͐��K������Ă���K�v������)
	static Quaternion MakeAxisAngle(const Vector3& axis, float angle);
	// �x�N�g����Quaternion�ŉ�]������
	static Vector3 RotateVector(const Vector3& v, const Quaternion& q);
	// Quaternion�����]�s������߂�
	static Matrix4 MakeRotateMatrix(const Quaternion& q);
};

float Dot(const Quaternion& q1, const Quaternion& q2);
// 2�����Z�q�I�[�o�[���[�h
Quaternion operator+(const Quaternion& q1, const Quaternion& q2);
Quaternion operator-(const Quaternion& q1, const Quaternion& q2);
Quaternion operator*(const Quaternion& q1, const Quaternion& q2);
Quaternion operator/(const Quaternion& q, float norm);

// ���ʐ��`���
Quaternion Slerp(const Quaternion& q0, const Quaternion& q1, float t);

// u����v�ւ̉�]�𐶐�(u,v�͐��K������Ă���O��)
Quaternion DirectionToDirection(const Vector3& u, const Vector3& v);