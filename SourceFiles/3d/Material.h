#pragma once
#include "Sprite.h"
#include <sstream>

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
		std::array<TextureTransform, 4> texTrans;
		std::array<ColorRGBA, 2> color; // �F
		std::array<float, 3> maskPow; // �}�X�N�̋���
	};

	std::string materialName;
	ColorRGB ambient = { 0.3f,0.3f,0.3f };
	ColorRGB diffuse;
	ColorRGB specular;
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffer;	// �萔�o�b�t�@
	ConstBufferData* constMap = nullptr;
	std::array<std::unique_ptr<Sprite>, (size_t)TexType::Num> sprites; // �e�N�X�`���̔z��

	size_t textureNum = 0;

	void LoadSprite(std::istringstream& line_stream, Mesh* mesh, TexType spriteIndex);

public:
	void Load(Mesh* mesh); // �}�e���A���ǂݍ���
	void SetAnbient(ColorRGB anbient_) { ambient = anbient_; }
	void SetDiffuse(ColorRGB diffuse_) { diffuse = diffuse_; }
	void SetSpecular(ColorRGB specular_) { specular = specular_; }
	void SetSprite(std::unique_ptr<Sprite> sprite, TexType type) { sprites[(size_t)type] = move(sprite); }
	void SetDissolvePow(float dissolve) { constMap->maskPow[2] = dissolve; }
	Sprite* GetSprite(TexType type) { return sprites[(size_t)type].get(); }
	void Update();
	void Draw();
};