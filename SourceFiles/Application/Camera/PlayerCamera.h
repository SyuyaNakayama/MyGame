#pragma once
#include "BaseCamera.h"

// ��ŏ������C�����邽�߂̎Q�l����
// https://docs.google.com/presentation/d/1XNAtNpD0L91TbVdtewIjw1vmtithvjUjOqEj-8s6TSE/edit#slide=id.g22dd4f4a57f_0_213

// �v���C���[�ɒǏ]����J����
class PlayerCamera : public BaseCamera
{
	Vector3 parentPrePos;
	
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="parent">���[���h�g�����X�t�H�[���̐e�|�C���^</param>
	void Initialize(WorldTransform* parent);
	// �X�V
	void Update();
};