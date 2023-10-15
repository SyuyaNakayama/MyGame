#pragma once
#include <vector>
#include "Sprite.h"

// �r�b�g�}�b�v�̓ǂݎ��ϐ��̎󂯓n���\����
struct BitMapProp
{
	//�r�b�g�}�b�v������摜�̃t�@�C����
	std::string fileName;
	// 1�������̃T�C�Y
	Vector2 rectSize;
	// �`��T�C�Y
	Vector2 size;
	// �`��ʒu(�s�N�Z�����W)
	Vector2 pos;
	// �\������
	int digit = 0;
};

/// <summary>
/// �r�b�g�}�b�v�̐����̕`��
/// �����ɂ̂ݑΉ�
/// </summary>
class BitMapNumber
{
private:
	std::vector<std::unique_ptr<Sprite>> sprites;

public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="bitMapProp">�r�b�g�}�b�v�v���p�e�B</param>
	void Initialize(const BitMapProp& bitMapProp);
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="number">�`�悷�鐔��</param>
	void Update(int number);
	// �`��
	void Draw();
	// �X�v���C�g�̐F�ς�
	void ChangeColor(const ColorRGBA& color);
};