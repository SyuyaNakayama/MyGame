#include "SpawnObject.h"
#include "Quaternion.h"
#include "Input.h"
#include "SceneManager.h"
#include "Random.h"

std::list<std::unique_ptr<GameObject>>* SpawnObject::objects;

void SpawnObject::Initialize(const ObjectData& objectData_)
{
	objectData = objectData_;
	spawnTimer = objectData_.spawnInterval;
	initialPos = objectData_.worldTransform->translation;
}

void SpawnObject::Update()
{
	if (SceneManager::GetInstance()->GetNowScene() == Scene::Play)
	{
		Angle spawnPosAngle = Random_Float(0, 2.0f * PI)();
		float distance = Random_Float(10.0f, 100.0f)();
		objectData.worldTransform->translation.x = cos(spawnPosAngle) * distance;
		objectData.worldTransform->translation.z = sin(spawnPosAngle) * distance;
	}
	if (!spawnTimer.Update() || objects->size() > SPAWN_MAX) { return; }
	std::unique_ptr<Object> newObj = std::make_unique<Object>();
	ObjectData objectDataTemp = objectData;
	objectDataTemp.worldTransform = new WorldTransform;
	*objectDataTemp.worldTransform = *objectData.worldTransform;
	objectDataTemp.worldTransform->Initialize();
	newObj->Initialize(objectDataTemp);
	objects->push_back(std::move(newObj));
}