#include "Stage.h"
#include <imgui.h>
#include "SceneManager.h"

int Stage::score = 0;
float Stage::STAGE_TIME = 60.0f;

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
		// オブジェクトの登録
		if (gameObject)
		{
			gameObject->Initialize(objectData);
			gameObjects.push_back(std::move(gameObject));
		}
	}

	stageTime = STAGE_TIME;
}

void Stage::Update()
{
	// ゲームが終わったかの確認
	if (stageTime.Update()) { isFinished = true; }
	// 消えた障害物のインスタンス削除
	gameObjects.remove_if([](std::unique_ptr<GameObject>& gameObject)
		{
			Object* object = dynamic_cast<Object*>(gameObject.get());
			if (object)
			{
				if (object->IsDestroy()) { return true; }
			}
			return false;
		});

	// 全ゲームオブジェクトの更新
	for (auto& gameObject : gameObjects) { gameObject->Update(); }
}