#include "Stage.h"
#include <imgui.h>
#include "SceneManager.h"

int Stage::score = 0;

void Stage::Initialize()
{
	SpawnObject::SetObjectList(&gameObjects);
	levelData = JsonLoader::LoadJson("stage");

	std::unique_ptr<GameObject> gameObject;
	for (auto& objectData : levelData->objects)
	{
		if (objectData.fileName == "cube" || objectData.fileName == "Ground")
		{
			gameObject = std::make_unique<Block>();
		}
		else if (objectData.fileName == "Goal")
		{
			gameObject = std::make_unique<Goal>();
		}
		else if (objectData.fileName == "Player")
		{
			gameObject = std::make_unique<Player>();
		}
		else if (objectData.fileName == "Object")
		{
			gameObject = std::make_unique<Object>();
		}
		else if (objectData.fileName == "SpawnPoint")
		{
			gameObject = std::make_unique<SpawnObject>();
			int spawnInterval = 0;
			if (SceneManager::GetInstance()->GetNowScene() == Scene::Play) { spawnInterval = 50; }
			else { spawnInterval = 180; }
			objectData.spawnInterval = spawnInterval;
		}
		// �I�u�W�F�N�g�̓o�^
		if (gameObject)
		{
			gameObject->Initialize(objectData);
			gameObjects.push_back(std::move(gameObject));
		}
	}

	fps = FPS::GetInstance()->GetMaxFPS();
	ResetTime();
}

void Stage::Update()
{
	// �Q�[�����I��������̊m�F
	if (stageTime.Update()) { isFinished = true; }
	// ��������Q���̃C���X�^���X�폜
	gameObjects.remove_if([](std::unique_ptr<GameObject>& gameObject)
		{
			Object* object = dynamic_cast<Object*>(gameObject.get());
			if (object)
			{
				if (object->IsDestroy()) { return true; }
			}
			return false;
		});

	// �S�Q�[���I�u�W�F�N�g�̍X�V
	for (auto& gameObject : gameObjects) { gameObject->Update(); }
}

std::array<int, 2> Stage::GetRemainTime()
{
	std::array<float, 2> timef{};
	// �~���b���擾���邽�߂̕ϐ�
	const float KILO = 1000.0f;
	// �c�莞�Ԃ��擾
	float t = (float)stageTime.GetRemainTime() / fps;
	// �������Ə������𕪗�
	timef[1] = modf(t, &timef[0]);
	return std::array<int, 2>({ (int)timef[0], (int)(timef[1] * KILO) });
}