#pragma once
#include "Collider.h"
#include "GameObject.h"
#include "TutorialEventManager.h"

// �S�[���ɉ^�ԃI�u�W�F�N�g
class Object : public WristerEngine::SphereCollider, public WristerEngine::BoxCollider, public WristerEngine::_3D::GameObject
{
private:
	static int instanceNum;

	WristerEngine::_3D::Object3d* object = nullptr;
	bool isGoal = false;
	float dissolvePow = 0;
	TutorialEventManager* eventManager = nullptr;
	ObjectType type = ObjectType::White;

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
	bool IsDestroy() const { return object->isDestroy; }
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