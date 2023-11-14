#pragma once
#include "BaseSpawnPoint.h"
#include "Object.h"

// �I�u�W�F�N�g�����I�u�W�F�N�g
class SpawnObject : public BaseSpawnPoint, public GameObject
{
	static std::list<std::unique_ptr<GameObject>>* objects;
	ObjectData objectData;
	Vector3 initialPos;
	static const int SPAWN_MAX = 300;

public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="objectData_">Json�t�@�C������ǂݍ��񂾃f�[�^</param>
	void Initialize(const ObjectData& objectData_);
	// �X�V
	void Update();
	// setter
	static void SetObjectList(std::list<std::unique_ptr<GameObject>>* list) { objects = list; }
};