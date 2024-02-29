#pragma once
#include "BaseCamera.h"

// ��ŏ������C�����邽�߂̎Q�l����
// https://docs.google.com/presentation/d/1XNAtNpD0L91TbVdtewIjw1vmtithvjUjOqEj-8s6TSE/edit#slide=id.g22dd4f4a57f_0_213

// �v���C���[�ɒǏ]����J����
class PlayerCamera : public WristerEngine::_3D::BaseCamera
{
	Vector3 parentPrePos;
	float rotSpdDec = 25;
	
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="parent">���[���h�g�����X�t�H�[���̐e�|�C���^</param>
	void Initialize(WristerEngine::_3D::Transform* parent);
	// �X�V
	void Update();
	// ��]�̑��x�␳�̐ݒ�
	void SetRotSpdDec(float rotSpdDec_) { rotSpdDec = rotSpdDec_; }
};