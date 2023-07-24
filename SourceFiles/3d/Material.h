#pragma once
#include "Sprite.h"

class Mesh;

struct TextureTransform
{
	Vector2 uvOffset;  // uv���炵
	Vector2 tiling; // �^�C�����O
};

enum class TexType { Main, Sub, Blend, Specular, Dissolve, Num };

// �}�e���A��
class Material
{
private:

	// �}�e���A��
	struct ConstBufferData
	{
		ColorRGBA ambient; // �p�f�B���O�܂�
		ColorRGBA diffuse;
		ColorRGBA specular;
		//TextureTransform texTrans[4];
		//ColorRGBA color[2]; // �F
		Vector2 uvOffset;  // uv���炵
		Vector2 tiling; // �^�C�����O
		ColorRGBA color; // �F
	};

	std::string materialName;
	ColorRGB ambient = { 0.3f,0.3f,0.3f };
	ColorRGB diffuse;
	ColorRGB specular;
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffer;	// �萔�o�b�t�@
	ConstBufferData* constMap = nullptr;
	std::array<std::unique_ptr<Sprite>,(size_t)TexType::Num> sprites; // �e�N�X�`���̘A�z�z��

public:
	void Load(Mesh* mesh); // �}�e���A���ǂݍ���
	void SetAnbient(ColorRGB anbient_) { ambient = anbient_; }
	void SetDiffuse(ColorRGB diffuse_) { diffuse = diffuse_; }
	void SetSpecular(ColorRGB specular_) { specular = specular_; }
	void SetSprite(std::unique_ptr<Sprite> sprite_) { sprites[(size_t)TexType::Main] = move(sprite_); }
	Sprite* GetSprite() { return sprites[(size_t)TexType::Main].get(); }
	void Update();
	void Draw();
};