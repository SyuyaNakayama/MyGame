#pragma once
#include "BaseSpawnPoint.h"
#include "Object.h"

// �I�u�W�F�N�g�����I�u�W�F�N�g
class SpawnObject : public WristerEngine::BaseSpawnPoint, public WristerEngine::_3D::GameObject
{
	
	static std::list<std::unique_ptr<WristerEngine::_3D::GameObject>>* objects;
	WristerEngine::ObjectData objectData;
	Vector3 initialPos;
	static const int SPAWN_MAX = 25;

public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="objectData_">Json�t�@�C������ǂݍ��񂾃f�[�^</param>
	void Initialize(const WristerEngine::ObjectData& objectData_);
	// �X�V
	void Update();
	// setter
	static void SetObjectList(std::list<std::unique_ptr<WristerEngine::_3D::GameObject>>* list) { objects = list; }
};