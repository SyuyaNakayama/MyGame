#pragma once
#include <vector>
#include "Sprite.h"

// ビットマップの読み取り変数の受け渡し構造体
struct BitMapProp
{
	//ビットマップがある画像のファイル名
	std::string fileName;
	// 1文字分のサイズ
	Vector2 rectSize;
	// 描画サイズ
	Vector2 size;
	// 描画位置(ピクセル座標)
	Vector2 pos;
	// 表示桁数
	int digit = 0;
};

/// <summary>
/// ビットマップの数字の描画
/// 整数にのみ対応
/// </summary>
class BitMapNumber
{
private:
	std::vector<std::unique_ptr<Sprite>> sprites;

public:
	void Initialize(const BitMapProp& bitMapProp);
	void Update(int number);
	void Draw();
	void ChangeColor(const ColorRGBA& color);
};