#include "SpawnObject.h"
#include "TutorialEvent.h"
#include <cassert>

using namespace WristerEngine::_3D;

SpawnObjectManager* SpawnObjectManager::GetInstance()
{
	static SpawnObjectManager instance;
	return &instance;
}

void SpawnObjectManager::AddObject(const ObjectData& objectData)
{
	std::unique_ptr<Object> newObj = std::make_unique<Object>();
	ObjectData objectDataTemp = objectData;
	objectDataTemp.worldTransform = new WristerEngine::_3D::Transform;
	*objectDataTemp.worldTransform = *objectData.worldTransform;
	objectDataTemp.worldTransform->Initialize();
	objectDataTemp.objectType = spawnObject->GetType();
	newObj->Initialize(objectDataTemp);
	objects->push_back(std::move(newObj));
}

void SpawnObjectManager::SetSpawnObject(GameObject* spawnObject_)
{
	spawnObject = dynamic_cast<BaseSpawnObject*>(spawnObject_);
	assert(spawnObject);
}

void SpawnObjectManager::ChangeSpawnObject()
{
	if (!nextSpawnObject) { return; }
	objects->remove_if([&](const std::unique_ptr<GameObject>& gameObject)
		{
			if (gameObject.get() == spawnObject) { return true; }
			return false;
		});
	SetSpawnObject(nextSpawnObject.get());
	objects->push_back(std::move(nextSpawnObject));
}

void SpawnObjectManager::ReserveChange(std::unique_ptr<WristerEngine::_3D::GameObject> spawnObject_)
{
	nextSpawnObject = std::move(spawnObject_);
}

void BaseSpawnObject::Initialize(const ObjectData& objectData_)
{
	// ���ǂݎ��
	objectData = objectData_;
	spawnTimer = objectData_.spawnInterval;
	initialPos = objectData_.worldTransform->translation;
	SPAWN_MAX = std::make_unique<const int>(objectData_.spawnMax);
}

void BaseSpawnObject::Update()
{
	if (!spawnTimer.Update() || Object::GetInstanceNum() >= *SPAWN_MAX) { return; }
	// �I�u�W�F�N�g�̐���
	manager->AddObject(objectData);
}

void SpawnObject::Initialize(const ObjectData& objectData_)
{
	BaseSpawnObject::Initialize(objectData_);
	roulette.Initialize({ 6,1,1 });
}

void SpawnObject::Update()
{
	if (GetNowScene() != Scene::Title)
	{
		// �����ʒu�𗐐��ŕύX
		Angle spawnPosAngle = WristerEngine::Random_Float(0, 2.0f * PI)();
		float distance = WristerEngine::Random_Float(10.0f, 100.0f)();
		objectData.worldTransform->translation.x = cos(spawnPosAngle) * distance;
		objectData.worldTransform->translation.z = sin(spawnPosAngle) * distance;
	}

	BaseSpawnObject::Update();
}

ObjectType SpawnObject::GetType()
{
	size_t rNum = roulette();

	switch (rNum)
	{
	case 0:	return ObjectType::White;
	case 1:	return ObjectType::Red;
	case 2:	return ObjectType::Green;
	}
	return ObjectType::White;
}

void TutorialSpawnObject::Initialize(const ObjectData& objectData_)
{
	BaseSpawnObject::Initialize(objectData_);
	tutorialEventPhase = tutorialEvent->GetTutorialEventPhase();
}

void TutorialSpawnObject::Update()
{
	if (tutorialEvent->IsEnd())
	{
		// �X�|�[���I�u�W�F�N�g���v���C�V�[���p�ɂ���
		std::unique_ptr<GameObject> newSpawnObject = std::make_unique<SpawnObject>();
		objectData.spawnMax = 10;
		newSpawnObject->Initialize(objectData);
		manager->ReserveChange(std::move(newSpawnObject));
		return;
	}

	phase = tutorialEvent->GetPhase();
	if (IsAny(phase, *tutorialEventPhase)) { BaseSpawnObject::Update(); }
}

ObjectType TutorialSpawnObject::GetType()
{
	if (phase == (*tutorialEventPhase)[0]) { return ObjectType::White; }
	if (phase == (*tutorialEventPhase)[1]) { return ObjectType::Red; }
	return ObjectType::Green;
}