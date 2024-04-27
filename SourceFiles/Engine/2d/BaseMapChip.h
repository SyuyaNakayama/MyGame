#pragma once
#include "Sprite.h"

namespace WristerEngine::_2D
{
	// �}�b�v�`�b�v�`��ėp�N���X
	class BaseMapChip
	{
	protected:
		Vector2 leftTopPos; // �N�_�ƂȂ�ʒu
		Vector2 chipSize; // �`�b�v1���̃T�C�Y
		Vector2 chipAnchor; // �`�b�v�̃A���J�[�|�C���g
		std::vector<std::unique_ptr<Sprite>> sprites; // �`��Ɏg���X�v���C�g

	public:
		virtual ~BaseMapChip() = default;

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="leftTopPos">�N�_�ƂȂ�ʒu</param>
		/// <param name="chipSize">�`�b�v1���̃T�C�Y</param>
		/// <param name="chipAnchor">�`�b�v�̃A���J�[�|�C���g</param>
		void Initialize(const Vector2& leftTopPos, const Vector2& chipSize, const Vector2& chipAnchor);

		virtual void VirtualInitialize(Sprite* sprite, float splitNum) = 0;

		/// <summary>
		/// �X�v���C�g���ǉ�
		/// </summary>
		/// <param name="fileName">�e�N�X�`���t�@�C����</param>
		/// <param name="chipPos">�`�b�v�P�ʂł̏ꏊ</param>
		/// <param name="splitNum">������</param>
		/// <param name="drawSize">�`��T�C�Y(0,0���ƋK��T�C�Y)</param>
		void AddSprite(const std::string& fileName, const Vector2& chipPos, float splitNum = 2.0f, const Vector2& drawSize = {});

		// �X�V
		virtual void Update() = 0;
		// �`��
		void Draw();
	};
}