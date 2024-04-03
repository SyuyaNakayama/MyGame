#pragma once
#include "Collider.h"
#include "GameObject.h"

// ���ƕǂ̃I�u�W�F�N�g
class Block : public WristerEngine::BoxCollider, public WristerEngine::_3D::GameObject
{
	WristerEngine::_3D::Object3d* object = nullptr;
	Vector3 normal;

public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="objectData">Json�t�@�C������ǂݍ��񂾃f�[�^</param>
	void Initialize(const ObjectData& objectData);
	// �X�V
	void Update() {}
	// �Փ˃R�[���o�b�N�֐�(BoxCollider��)
	void OnCollision(BoxCollider* collider);
};