#pragma once
#include <vector>
#include "Sprite.h"

namespace WristerEngine::_2D
{
	// �r�b�g�}�b�v�̓ǂݎ��ϐ��̎󂯓n���\����
	struct BitMapProp
	{
		// �r�b�g�}�b�v������摜�̃t�@�C����
		std::string fileName;
		// 1�������̃T�C�Y
		Vector2 rectSize;
		// �`��T�C�Y
		Vector2 size;
		// �`��ʒu(�s�N�Z�����W)
		Vector2 pos;
		// �\������
		int digit = 0;
		// �F����
		ColorRGBA color;
		// �؂���̈�̍�����W�̃I�t�Z�b�g
		Vector2 texLTOffset;
		// �A���J�[�|�C���g
		Vector2 anchorPoint;

		/// <summary>
		/// BitMapNumber�������ɕK�v�Ȓl�̃Z�b�g
		/// </summary>
		/// <param name="fileName">�r�b�g�}�b�v������摜�̃t�@�C����</param>
		/// <param name="rectSize">1�������̃T�C�Y</param>
		/// <param name="size">�`��T�C�Y</param>
		/// <param name="pos">�`��ʒu(�s�N�Z�����W)</param>
		/// <param name="digit">�\������</param>
		void SetVal(const std::string& fileName, Vector2 rectSize, Vector2 size, Vector2 pos, int digit);
	};

	/// <summary>
	/// �r�b�g�}�b�v�̐����̕`��
	/// �����ɂ̂ݑΉ�
	/// </summary>
	class BitMapNumber
	{
	private:
		std::vector<std::unique_ptr<WristerEngine::_2D::Sprite>> sprites;
		BitMapProp bitMapProp;
		Vector2 allSpriteSize; // �X�v���C�g�S�̂̑傫��

		/// <summary>
		/// �X�v���C�g�̍X�V(Initialize,Update�֐��̋��ʕ���)
		/// </summary>
		/// <param name="index">sprites�̃C���f�b�N�X</param>
		void UpdateSprite(size_t index);

	public:
		// ������
		void Initialize();

		/// <summary>
		/// �X�V
		/// </summary>
		/// <param name="number">�`�悷�鐔��</param>
		void Update(int number);
		// �`��
		void Draw();
		/// <summary>
		/// bitMapProp���擾
		/// </summary>
		/// <returns>bitMapProp�̃|�C���^</returns>
		BitMapProp* GetBitMapProp() { return &bitMapProp; }
		// �X�v���C�g�S�̂̑傫�����擾
		Vector2 GetAllSpriteSize() const { return allSpriteSize; }
	};
}