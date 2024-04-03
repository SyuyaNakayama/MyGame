#pragma once
#include "AbstractSpawnPoint.h"
#include "Object.h"
#include "Random.h"

// �O����`
class BaseSpawnObject;

// �`���[�g���A���V�[����SpawnObject���`���[�g���A���p����v���C�p�ɐ؂�ւ��邽�߂̃}�l�[�W���[�N���X
class SpawnObjectManager final
{
private:
	std::list<std::unique_ptr<WristerEngine::_3D::GameObject>>* objects = nullptr;
	BaseSpawnObject* spawnObject = nullptr;
	std::unique_ptr<WristerEngine::_3D::GameObject> nextSpawnObject;

	SpawnObjectManager() = default;
	~SpawnObjectManager() = default;

public:
	/// <summary>
	/// �C���X�^���X�擾
	/// </summary>
	/// <returns>SpawnObjectmanager�C���X�^���X</returns>
	static SpawnObjectManager* GetInstance();

	SpawnObjectManager(const SpawnObjectManager& obj) = delete;
	SpawnObjectManager& operator=(const SpawnObjectManager& obj) = delete;

	// �I�u�W�F�N�g��ǉ�
	void AddObject(const ObjectData& objectData);
	// ObjectList���Z�b�g
	void SetObjectList(std::list<std::unique_ptr<WristerEngine::_3D::GameObject>>* list) { objects = list; }
	// SpawnObject���Z�b�g
	void SetSpawnObject(WristerEngine::_3D::GameObject* spawnObject_);
	// SpawnObject��ύX
	void ChangeSpawnObject();
	// SpawnObject��ύX����\�������
	void ReserveChange(std::unique_ptr<WristerEngine::_3D::GameObject> spawnObject);
};

// ���̃Q�[���ł̃X�|�[���I�u�W�F�N�g���N���X
class BaseSpawnObject : public WristerEngine::AbstractSpawnPoint, public WristerEngine::_3D::GameObject
{
protected:
	SpawnObjectManager* manager = SpawnObjectManager::GetInstance();
	ObjectData objectData;
	Vector3 initialPos;
	std::unique_ptr<const int> SPAWN_MAX = nullptr;

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
};

// �I�u�W�F�N�g�����I�u�W�F�N�g
class SpawnObject : public BaseSpawnObject
{
	WristerEngine::Roulette roulette;

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