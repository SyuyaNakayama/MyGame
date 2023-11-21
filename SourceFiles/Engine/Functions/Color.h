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

	// �F�擾
	static ColorRGB Red() { return { 1,0,0 }; }
	static ColorRGB Green() { return { 0,1,0 }; }
	static ColorRGB Blue() { return { 0,0,1 }; }
	static ColorRGB White() { return { 1,1,1 }; }
	static ColorRGB Black() { return { 0,0,0 }; }
	static ColorRGB Yellow() { return { 1,1,0 }; }
	static ColorRGB Magenta() { return { 1,0,1 }; }
	static ColorRGB Cyan() { return { 0,1,1 }; }
};

// �J���[�lRGBA
struct ColorRGBA
{
	Color r, g, b, a;
	// �R���X�g���N�^
	ColorRGBA() {}
	ColorRGBA(float red, float green, float blue, float alpha = Color::MAX) { r = red, g = green, b = blue, a = alpha; }
	ColorRGBA(ColorRGB color, float alpha = Color::MAX) { r = color.r, g = color.g, b = color.b, a = alpha; }

	// �F�擾
	static ColorRGBA Red() { return { 1,0,0,1 }; }
	static ColorRGBA Green() { return { 0,1,0,1 }; }
	static ColorRGBA Blue() { return { 0,0,1,1 }; }
	static ColorRGBA White() { return { 1,1,1,1 }; }
	static ColorRGBA Black() { return { 0,0,0,1 }; }
	static ColorRGBA Yellow() { return { 1,1,0,1 }; }
	static ColorRGBA Magenta() { return { 1,0,1,1 }; }
	static ColorRGBA Cyan() { return { 0,1,1,1 }; }
};