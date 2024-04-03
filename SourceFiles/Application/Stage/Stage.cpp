#include "Stage.h"
#include "Goal.h"
#include <imgui.h>
#include "SceneManager.h"

using namespace WristerEngine::_3D;

int Stage::score = 0;
float Stage::GROUND_POS_Y = 5.0f;

void Stage::Initialize()
{
	// 静的初期化
	spawnObjectManager->SetObjectList(&gameObjects);
	Goal::StaticInitialize();

	levelData = LevelLoader::LoadLevel("stage");

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
			std::map<Scene, int> spawnIntervals = {
				{Scene::Title,180},
				{Scene::Tutorial,1},
				{Scene::Play,1}
			};
			Scene nowScene = WristerEngine::SceneManager::GetInstance()->GetNowScene();
			objectData.spawnMax = 10;

			if (nowScene == Scene::Tutorial)
			{
				gameObject = std::make_unique<TutorialSpawnObject>();
				objectData.spawnMax = 1;
			}
			else { gameObject = std::make_unique<SpawnObject>(); }
			objectData.spawnInterval = spawnIntervals[nowScene];
			spawnObjectManager->SetSpawnObject(gameObject.get());
		}
		// オブジェクトの登録
		if (gameObject)
		{
			gameObject->Initialize(objectData);
			gameObjects.push_back(std::move(gameObject));
		}
	}

	fps = WristerEngine::MAX_FPS;
	ResetTime();
}

void Stage::Update()
{
	// ゲームが終わったかの確認
	if (stageTime.Update()) { isFinished = true; }
	// 消えた障害物のインスタンス削除
	gameObjects.remove_if([](const std::unique_ptr<GameObject>& gameObject)
		{
			Object* object = dynamic_cast<Object*>(gameObject.get());
			if (object)
			{
				if (object->IsDestroy()) { return true; }
			}
			return false;
		});

	spawnObjectManager->ChangeSpawnObject();

	// ゴールの静的更新
	Goal::StaticUpdate();
	// 全ゲームオブジェクトの更新
	for (auto& gameObject : gameObjects)
	{
		gameObject->Update();
	}
}

std::array<int, 2> Stage::GetRemainTime() const
{
	return stageTime.GetRemainTime(fps);
}