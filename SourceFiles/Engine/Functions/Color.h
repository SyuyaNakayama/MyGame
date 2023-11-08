#pragma once

// 1色分の構造体
struct Color
{
public:
	// カラーの最大値
	static const float MAX;

private:
	float val_ = Color::MAX;

public:
	float operator=(float val);
	void operator+=(float val) { operator=(val_ + val); }
	void operator-=(float val) { operator=(val_ - val); }
	operator float() { return val_; }
};

// カラー値RGB
struct ColorRGB
{
	Color r, g, b;
	// コンストラクタ
	ColorRGB() {}
	ColorRGB(float red, float green, float blue) { r = red, g = green, b = blue; }
};

// カラー値RGBA
struct ColorRGBA
{
	Color r, g, b, a;
	// コンストラクタ
	ColorRGBA() {}
	ColorRGBA(float red, float green, float blue, float alpha = Color::MAX) { r = red, g = green, b = blue, a = alpha; }
	ColorRGBA(ColorRGB color, float alpha = Color::MAX) { r = color.r, g = color.g, b = color.b, a = alpha; }
};