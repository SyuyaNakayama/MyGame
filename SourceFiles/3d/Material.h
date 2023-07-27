#pragma once
#include "Sprite.h"
#include <sstream>

class Mesh;

struct TextureTransform
{
	Vector2 uvOffset;  // uvずらし
	Vector2 tiling; // タイリング
};

enum class TexType { Main, Sub, Blend, Specular, Dissolve, Num };

// マテリアル
struct Material
{
	std::string materialName;
	ColorRGB ambient = { 0.3f,0.3f,0.3f };
	ColorRGB diffuse;
	ColorRGB specular;

	void Load(Mesh* mesh); // マテリアル読み込み
	void SetDissolvePow(float dissolve) { constMap->maskPow[2] = dissolve; }
	void Update();
	void Draw();
	Sprite* GetSprite(TexType texType) { return sprites[(size_t)texType].get(); }
	void SetSprite(std::unique_ptr<Sprite> sprite, TexType type) { sprites[(size_t)type] = move(sprite); }
	void TransferCBV();

private:
	// マテリアル
	struct ConstBufferData
	{
		ColorRGBA ambient; // パディング含む
		ColorRGBA diffuse;
		ColorRGBA specular;
		std::array<TextureTransform, 4> texTrans;
		std::array<ColorRGBA, 2> color; // 色
		std::array<float, 3> maskPow; // マスクの強さ
	};

	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffer;	// 定数バッファ
	ConstBufferData* constMap = nullptr;

	std::array<std::unique_ptr<Sprite>, (size_t)TexType::Num> sprites; // テクスチャの配列
	void LoadSprite(std::istringstream& line_stream, Mesh* mesh, TexType spriteIndex);
};