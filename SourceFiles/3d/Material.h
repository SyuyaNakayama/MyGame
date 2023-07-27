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
struct Material
{
	std::string materialName;
	ColorRGB ambient = { 0.3f,0.3f,0.3f };
	ColorRGB diffuse;
	ColorRGB specular;

	void Load(Mesh* mesh); // �}�e���A���ǂݍ���
	void SetDissolvePow(float dissolve) { constMap->maskPow[2] = dissolve; }
	void Update();
	void Draw();
	Sprite* GetSprite(TexType texType) { return sprites[(size_t)texType].get(); }
	void SetSprite(std::unique_ptr<Sprite> sprite, TexType type) { sprites[(size_t)type] = move(sprite); }
	void TransferCBV();

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

	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffer;	// �萔�o�b�t�@
	ConstBufferData* constMap = nullptr;

	std::array<std::unique_ptr<Sprite>, (size_t)TexType::Num> sprites; // �e�N�X�`���̔z��
	void LoadSprite(std::istringstream& line_stream, Mesh* mesh, TexType spriteIndex);
};