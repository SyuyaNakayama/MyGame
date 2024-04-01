#pragma once
#include "AbstractSpawnPoint.h"
#include "Object.h"
#include "Random.h"

// ���̃Q�[���ł̃X�|�[���I�u�W�F�N�g���N���X
class BaseSpawnObject : public WristerEngine::AbstractSpawnPoint, public WristerEngine::_3D::GameObject
{
protected:
	static std::list<std::unique_ptr<WristerEngine::_3D::GameObject>>* objects;
	ObjectData objectData;
	Vector3 initialPos;
	std::unique_ptr<const int> SPAWN_MAX = nullptr;
	WristerEngine::Roulette roulette;

public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="objectData">Json�t�@�C������ǂݍ��񂾃f�[�^</param>
	virtual void Initialize(const ObjectData& objectData);

	// �X�V
	virtual void Update();

	// Type��ݒ�
	virtual ObjectType GetType() = 0;

	// ObjectList���Z�b�g
	static void SetObjectList(std::list<std::unique_ptr<WristerEngine::_3D::GameObject>>* list) { objects = list; }
};

// �I�u�W�F�N�g�����I�u�W�F�N�g
class SpawnObject : public BaseSpawnObject
{

public:
	void Initialize(const ObjectData& objectData_) override;

	// �X�V
	void Update();

	// BaseSpawnObject ����Čp������܂���
	ObjectType GetType() override;
};

// �`���[�g���A���̃X�|�[���I�u�W�F�N�g
class TutorialSpawnObject : public BaseSpawnObject
{
private:
	UINT32 phase;
	const TutorialEvent* tutorialEvent = TutorialEvent::GetInstance();
	const std::vector<UINT32>* tutorialEventPhase = nullptr;

public:
	void Initialize(const ObjectData& objectData_) override;

	// �X�V
	void Update();

	// BaseSpawnObject ����Čp������܂���
	ObjectType GetType() override;
};