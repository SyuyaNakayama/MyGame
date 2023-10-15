#pragma once
#include "Vector.h"

// 4x4�s��
class Matrix4
{
public:
	float m[4][4] =
	{
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};
	Matrix4 operator*=(const Matrix4& m2);
	// �x�N�g���̑��
	void SetVector(Vector3& vec, size_t row);
	// �s�񂩂�x�N�g���𓾂�
	Vector3 GetVector(size_t row) const;

	// �P�ʍs��
	static Matrix4 Identity();
	// �[���s��
	static Matrix4 Zero();
	// �X�P�[���s��
	static Matrix4 Scale(const Vector3& s);
	// X������̉�]�s��
	static Matrix4 RotateX(float angle);
	// Y������̉�]�s��
	static Matrix4 RotateY(float angle);
	// Z������̉�]�s��
	static Matrix4 RotateZ(float angle);
	// ��]�s��
	static Matrix4 Rotate(const Vector3& r);
	// ���s�ړ��s��
	static Matrix4 Translate(const Vector3& t);
	// �]�u�s��
	static Matrix4 Transpose(const Matrix4& mat);
	// �t�s��
	static Matrix4 Inverse(const Matrix4& mat);
	// 3D�x�N�g������s������
	static Matrix4 CreateFromVector(const Vector3& vec1 = { 1,0,0 }, const Vector3& vec2 = { 0,1,0 }, const Vector3& vec3 = { 0,0,1 }, const Vector3& vec4 = {});
	// ���ݎg�p���Ă���J�����ɑ΂��Ẵr���{�[�h�s���Ԃ�
	static Matrix4 GetBillboard();
};

Matrix4 operator*(const Matrix4& m1, const Matrix4& m2);
Vector3 operator*(const Vector3& v, const Matrix4& m);