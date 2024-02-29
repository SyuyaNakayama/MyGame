#include "SpawnObject.h"
#include "SceneManager.h"
#include "Random.h"

std::list<std::unique_ptr<WristerEngine::_3D::GameObject>>* BaseSpawnObject::objects;

void BaseSpawnObject::Initialize(const WristerEngine::ObjectData& objectData_)
{
	// ���ǂݎ��
	objectData = objectData_;
	spawnTimer = objectData_.spawnInterval;
	initialPos = objectData_.worldTransform->translation;
}

void BaseSpawnObject::Update()
{
	// �I�u�W�F�N�g�̐���
	std::unique_ptr<Object> newObj = std::make_unique<Object>();
	WristerEngine::ObjectData objectDataTemp = objectData;
	objectDataTemp.worldTransform = new WristerEngine::_3D::Transform;
	*objectDataTemp.worldTransform = *objectData.worldTransform;
	objectDataTemp.worldTransform->Initialize();
	newObj->Initialize(objectDataTemp);
	objects->push_back(std::move(newObj));
}

void SpawnObject::Update()
{
	Scene nowScene = WristerEngine::SceneManager::GetInstance()->GetNowScene();
	if (nowScene == Scene::Play)
	{
		// �����ʒu�𗐐��ŕύX
		Angle spawnPosAngle = WristerEngine::Random_Float(0, 2.0f * PI)();
		float distance = WristerEngine::Random_Float(10.0f, 100.0f)();
		objectData.worldTransform->translation.x = cos(spawnPosAngle) * distance;
		objectData.worldTransform->translation.z = sin(spawnPosAngle) * distance;
	}

	if (!spawnTimer.Update() || objects->size() > SPAWN_MAX) { return; }
	BaseSpawnObject::Update();
}

void TutorialSpawnObject::Update()
{
	if (!spawnTimer.Update() || objects->size() > SPAWN_MAX) { return; }
	BaseSpawnObject::Update();
}