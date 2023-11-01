#pragma once

// 1�F���̍\����
struct Color
{
private:
	float val_ = 1.0f;

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
	ColorRGBA(float red, float green, float blue, float alpha = 1.0f) { r = red, g = green, b = blue, a = alpha; }
	ColorRGBA(ColorRGB color, float alpha = 1.0f) { r = color.r, g = color.g, b = color.b, a = alpha; }
};