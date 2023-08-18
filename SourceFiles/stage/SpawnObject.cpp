#include "SpawnObject.h"
#include "Quaternion.h"
#include "Input.h"

std::list<std::unique_ptr<Object>>* SpawnObject::objects;

void SpawnObject::Initialize(const ObjectData& objectData_, int spawnInterval)
{
	objectData = objectData_;
	spawnTimer = spawnInterval;
	initialPos = objectData_.worldTransform->translation;
}

void SpawnObject::Spawn()
{
	static bool a = false;
	if (Input::GetInstance()->IsTrigger(Key::Q)) { a = true; }
	if (!a) { return; }
	Quaternion rotQ = Quaternion::MakeAxisAngle(Vector3::MakeAxis(Axis::Y), spawnPosAngle);
	objectData.worldTransform->translation = Quaternion::RotateVector(initialPos, rotQ);
	spawnPosAngle++;
	if (!spawnTimer.CountDown()) { return; }
	std::unique_ptr<Object> newObj = std::make_unique<Object>();
	ObjectData objectDataTemp = objectData;
	objectDataTemp.worldTransform = new WorldTransform;
	*objectDataTemp.worldTransform = *objectData.worldTransform;
	objectDataTemp.worldTransform->Initialize();
	newObj->Initialize(objectDataTemp);
	objects->push_back(std::move(newObj));
}