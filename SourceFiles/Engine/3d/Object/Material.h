#pragma once
#include "Sprite.h"
#include <sstream>

namespace WristerEngine::_3D
{
	class Mesh;

	struct TextureTransform
	{
		Vector2 uvOffset;  // uv���炵
		Vector2 tiling; // �^�C�����O
	};

	// �e�N�X�`���̖���
	enum class TexType
	{
		Main,		// ���C���e�N�X�`��
		Sub,		// �T�u�e�N�X�`��
		Blend, 		// �u�����h�}�b�v
		Specular,	// �X�y�L�����}�b�v
		Dissolve,	// �f�B�]���u�}�b�v
		Num 		// �e�N�X�`����
	};

	// �}�e���A��
	struct Material
	{
		std::string materialName;
		ColorRGB ambient = { 0.3f,0.3f,0.3f };
		ColorRGB diffuse;
		ColorRGB specular;

		// �}�e���A���ǂݍ���
		void Load(Mesh* mesh);
		// �X�V
		void Update();
		// �`��
		void Draw();
		// �萔�o�b�t�@�ɓ]��
		void TransferCBV();
		// setter
		void SetDissolvePow(float dissolve) { constMap->maskPow[2] = dissolve; }
		void SetSprite(std::unique_ptr<_2D::Sprite> sprite, TexType type) { sprites[(size_t)type] = move(sprite); }
		// getter
		_2D::Sprite* GetSprite(TexType texType) { return sprites[(size_t)texType].get(); }

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

		std::array<std::unique_ptr<_2D::Sprite>, (size_t)TexType::Num> sprites; // �e�N�X�`���̔z��
		// �e�N�X�`���ǂݍ���
		void LoadSprite(std::istringstream& line_stream, Mesh* mesh, TexType spriteIndex);
	};
}