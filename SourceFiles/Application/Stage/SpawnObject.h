#pragma once
#include "AbstractSpawnPoint.h"
#include "Object.h"

// ���̃Q�[���ł̃X�|�[���I�u�W�F�N�g���N���X
class BaseSpawnObject : public WristerEngine::AbstractSpawnPoint, public WristerEngine::_3D::GameObject
{
protected:
	static std::list<std::unique_ptr<WristerEngine::_3D::GameObject>>* objects;
	WristerEngine::ObjectData objectData;
	Vector3 initialPos;

public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="objectData_">Json�t�@�C������ǂݍ��񂾃f�[�^</param>
	void Initialize(const WristerEngine::ObjectData& objectData_);

	// �X�V
	virtual void Update();

	// ObjectList���Z�b�g
	static void SetObjectList(std::list<std::unique_ptr<WristerEngine::_3D::GameObject>>* list) { objects = list; }
};

// �I�u�W�F�N�g�����I�u�W�F�N�g
class SpawnObject : public BaseSpawnObject
{
	static const int SPAWN_MAX = 25;

private:


public:
	// �X�V
	void Update();
};

// �`���[�g���A���̃X�|�[���I�u�W�F�N�g
class TutorialSpawnObject : public BaseSpawnObject
{
	static const int SPAWN_MAX = 2;

public:
	// �X�V
	void Update();
};