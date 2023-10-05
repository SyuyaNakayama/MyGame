#include "SpawnObject.h"
#include "Quaternion.h"
#include "Input.h"
#include "SceneManager.h"

std::list<std::unique_ptr<Object>>* SpawnObject::objects;

void SpawnObject::Initialize(const ObjectData& objectData_, int spawnInterval)
{
	objectData = objectData_;
	spawnTimer = spawnInterval;
	initialPos = objectData_.worldTransform->translation;
}

void SpawnObject::Spawn()
{
	if (SceneManager::GetInstance()->GetNowScene() == Scene::Play)
	{
		objectData.worldTransform->translation.x = cos(spawnPosAngle) * distance;
		objectData.worldTransform->translation.z = sin(spawnPosAngle * PI) * distance;
		spawnPosAngle++;
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