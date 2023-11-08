#pragma once

// 1�F���̍\����
struct Color
{
public:
	// �J���[�̍ő�l
	static const float MAX;

private:
	float val_ = Color::MAX;

public:
	float operator=(float val);
	void operator+=(float val) { operator=(val_ + val); }
	void operator-=(float val) { operator=(val_ - val); }
	operator float() { return val_; }
};

// �J���[�lRGB
struct ColorRGB
{
	Color r, g, b;
	// �R���X�g���N�^
	ColorRGB() {}
	ColorRGB(float red, float green, float blue) { r = red, g = green, b = blue; }
};

// �J���[�lRGBA
struct ColorRGBA
{
	Color r, g, b, a;
	// �R���X�g���N�^
	ColorRGBA() {}
	ColorRGBA(float red, float green, float blue, float alpha = Color::MAX) { r = red, g = green, b = blue, a = alpha; }
	ColorRGBA(ColorRGB color, float alpha = Color::MAX) { r = color.r, g = color.g, b = color.b, a = alpha; }
};