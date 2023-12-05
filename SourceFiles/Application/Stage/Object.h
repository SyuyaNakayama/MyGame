#pragma once
#include "Collider.h"
#include "GameObject.h"

// �S�[���ɉ^�ԃI�u�W�F�N�g
class Object : public SphereCollider, public BoxCollider, public GameObject
{
public:
	enum class Type
	{
		White = 0,	// �ʏ�
		Red = 6,	// �_��2�{
		Green = 7,	// �_��-1�{
		MaxNum = 7
	};

private:
	static int instanceNum;

	Object3d* object = nullptr;
	bool isGoal = false;
	float dissolvePow = 0;
	Type type = Type::White;

public:
	// �R���X�g���N�^
	Object() { instanceNum++; }
	// �f�X�g���N�^
	~Object() { instanceNum--; }
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="objectData">Json�t�@�C������ǂݍ��񂾃f�[�^</param>
	void Initialize(const ObjectData& objectData);
	// �X�V
	void Update();
	// �Փ˃R�[���o�b�N�֐�(SphereCollider��)
	void OnCollision(SphereCollider* collider);
	// �j�󂷂�
	void Destroy() { object->isDestroy = true; }
	// setter(isDestroy)
	bool IsDestroy() { return object->isDestroy; }
	// ���̃N���X�̃C���X�^���X�����擾
	static int GetInstanceNum() { return instanceNum; }
	// �S�[������
	void Goal() { isGoal = true; }
	/// <summary>
	/// �S�[���ɓ��ꂽ���̓_�����擾
	/// </summary>
	/// <param name="goalScore">�S�[���̓_��</param>
	/// <returns></returns>
	int GetGoalScore(int goalScore);
};