#include "Stage.h"
#include <imgui.h>
#include "SceneManager.h"

int Stage::score = 0;
float Stage::GROUND_POS_Y = 5.0f;

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
			const std::array<int, 2> SPAWN_INTERVALS = { 180,50 };
			bool isPlayScene = SceneManager::GetInstance()->GetNowScene() == Scene::Play;

			gameObject = std::make_unique<SpawnObject>();
			objectData.spawnInterval = SPAWN_INTERVALS[isPlayScene];
		}
		// オブジェクトの登録
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

std::array<int, 2> Stage::GetRemainTime()
{
	return stageTime.GetRemainTime(fps);
}