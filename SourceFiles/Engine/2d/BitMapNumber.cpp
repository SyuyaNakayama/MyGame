#include "BitMapNumber.h"

void BitMapNumber::Initialize(const BitMapProp& bitMapProp)
{
	for (size_t i = 0; i < bitMapProp.digit; i++)
	{
		// 数字のスプライト
		sprites.push_back(Sprite::Create(bitMapProp.fileName));
		sprites[i]->textureSize = bitMapProp.rectSize;
		sprites[i]->size = bitMapProp.size;

		// 配置
		Vector2 sprpos = bitMapProp.pos;
		sprpos.x += bitMapProp.size.x * i;
		sprites[i]->position = sprpos;
	}
}

void BitMapNumber::Update(int number)
{
	std::vector<int> numchar(sprites.size());
	bool isCountStop = log10(number) >= (double)sprites.size();

	// 桁の抽出
	for (int i = (int)sprites.size() - 1; i >= 0; i--)
	{
		if (!isCountStop)
		{
			numchar[i] = number % 10;
			number /= 10;
		}
		else { numchar[i] = 9; }
	}

	for (size_t i = 0; i < sprites.size(); i++)
	{
		sprites[i]->textureLeftTop = { numchar[i] * sprites[i]->textureSize.x,0.0f };
		sprites[i]->Update();
	}
}

void BitMapNumber::Draw()
{
	for (auto& spr : sprites) { spr->Draw(); }
}

void BitMapNumber::ChangeColor(const ColorRGBA& color)
{
	for (auto& spr : sprites) { spr->color = color; }
}