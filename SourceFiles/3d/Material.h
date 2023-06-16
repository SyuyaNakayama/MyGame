#pragma once
#include "Sprite.h"

class Mesh;

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
	std::unique_ptr<Sprite> sprite;		// �e�N�X�`��

public:
	void Load(Mesh* mesh); // �}�e���A���ǂݍ���
	void SetAnbient(ColorRGB anbient_) { ambient = anbient_; }
	void SetDiffuse(ColorRGB diffuse_) { diffuse = diffuse_; }
	void SetSpecular(ColorRGB specular_) { specular = specular_; }
	void SetSprite(std::unique_ptr<Sprite> sprite_) { sprite = move(sprite_); }
	Sprite* GetSprite() { return sprite.get(); }
	void Update();
	void Draw();
};