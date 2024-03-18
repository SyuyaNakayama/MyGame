#pragma once

namespace WristerEngine
{
	// 1�F���̍\����
	struct Color
	{
	public:
		// �J���[�̍ő�l
		static const float MAX;

	private:
		float val_ = Color::MAX;

	public:
		Color() = default;
		Color(float color) { val_ = color; }
		// ���Z�q�I�[�o�[���[�h
		float operator=(float val);
		Color operator*=(float rate) { val_ *= rate; return val_; }
		void operator+=(float val) { operator=(val_ + val); }
		void operator-=(float val) { operator=(val_ - val); }
		operator float() { return val_; }
	};

	// �J���[�lRGB
	struct ColorRGB
	{
		Color r, g, b;
		// �R���X�g���N�^
		ColorRGB() = default;
		ColorRGB(Color red, Color green, Color blue) { r = red, g = green, b = blue; }

		// ���Z�q�I�[�o�[���[�h
		ColorRGB& operator*=(float rate);

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
		ColorRGBA(Color red, Color green, Color blue, Color alpha = Color::MAX) { r = red, g = green, b = blue, a = alpha; }
		ColorRGBA(ColorRGB color, float alpha = Color::MAX) { r = color.r, g = color.g, b = color.b, a = alpha; }

		// ���Z�q�I�[�o�[���[�h
		ColorRGBA& operator*=(float rate);

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

	// 2�����Z�q�I�[�o�[���[�h
	const Color operator*(Color color, float rate);
	const ColorRGB operator*(ColorRGB color, float rate);
	const ColorRGBA operator*(ColorRGBA color, float rate);
}