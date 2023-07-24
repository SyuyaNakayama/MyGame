#pragma once
#include "Sprite.h"

class Mesh;

struct TextureTransform
{
	Vector2 uvOffset;  // uvずらし
	Vector2 tiling; // タイリング
};

enum class TexType { Main, Sub, Blend, Specular, Dissolve, Num };

// マテリアル
class Material
{
private:

	// マテリアル
	struct ConstBufferData
	{
		ColorRGBA ambient; // パディング含む
		ColorRGBA diffuse;
		ColorRGBA specular;
		//TextureTransform texTrans[4];
		//ColorRGBA color[2]; // 色
		Vector2 uvOffset;  // uvずらし
		Vector2 tiling; // タイリング
		ColorRGBA color; // 色
	};

	std::string materialName;
	ColorRGB ambient = { 0.3f,0.3f,0.3f };
	ColorRGB diffuse;
	ColorRGB specular;
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffer;	// 定数バッファ
	ConstBufferData* constMap = nullptr;
	std::array<std::unique_ptr<Sprite>,(size_t)TexType::Num> sprites; // テクスチャの連想配列

public:
	void Load(Mesh* mesh); // マテリアル読み込み
	void SetAnbient(ColorRGB anbient_) { ambient = anbient_; }
	void SetDiffuse(ColorRGB diffuse_) { diffuse = diffuse_; }
	void SetSpecular(ColorRGB specular_) { specular = specular_; }
	void SetSprite(std::unique_ptr<Sprite> sprite_) { sprites[(size_t)TexType::Main] = move(sprite_); }
	Sprite* GetSprite() { return sprites[(size_t)TexType::Main].get(); }
	void Update();
	void Draw();
};