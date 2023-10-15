#pragma once
#include "Collider.h"
#include "GameObject.h"

// ���ƕǂ̃I�u�W�F�N�g
class Block : public BoxCollider, public GameObject
{
	Object3d* object;
	Vector3 normal;

public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="objectData">Json�t�@�C������ǂݍ��񂾃f�[�^</param>
	void Initialize(const ObjectData& objectData);
	// �X�V
	void Update(){}
	// �Փ˃R�[���o�b�N�֐�(BoxCollider��)
	void OnCollision(BoxCollider* collider);
};

// �S�[���̃I�u�W�F�N�g
class Goal : public BoxCollider, public GameObject
{
	Object3d* object;
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