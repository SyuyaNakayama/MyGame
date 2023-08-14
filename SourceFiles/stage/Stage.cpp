#include "Stage.h"
#include <imgui.h>

int Stage::score = 0;

void Stage::Initialize()
{
	SpawnObject::SetObjectList(&objects);
	levelData = JsonLoader::LoadJson("stage");
	for (auto& objectData : levelData->objects)
	{
		if (objectData.fileName == "cube" || objectData.fileName == "Ground")
		{
			std::unique_ptr<Block> newBlock = std::make_unique<Block>();
			newBlock->Initialize(objectData);
			blocks.push_back(std::move(newBlock));
		}
		else if (objectData.fileName == "Goal")
		{
			std::unique_ptr<Goal> newGoal = std::make_unique<Goal>();
			newGoal->Initialize(objectData);
			goals.push_back(std::move(newGoal));
		}
		else if (objectData.fileName == "Player")
		{
			player.Initialize(objectData);
		}
		else if (objectData.fileName == "Object")
		{
			std::unique_ptr<Object> newObj = std::make_unique<Object>();
			newObj->Initialize(objectData);
			objects.push_back(std::move(newObj));
		}
		else if (objectData.fileName == "SpawnPoint")
		{
			SpawnObject spawnPoint;
			spawnPoint.Initialize(objectData, 50);
			spawnPoints.push_back(spawnPoint);
		}
	}
}

void Stage::Update()
{
	player.Update();
	objects.remove_if([](std::unique_ptr<Object>& object) { return object->IsDestroy(); });
	for (auto& spawnPoint : spawnPoints) { spawnPoint.Spawn(); }
	ImGui::Text("%d", objects.size());
	for (auto& block : blocks) { block->Update(); }
	for (auto& object : objects) { object->Update(); }
	for (auto& goal : goals) { goal->Update(); }
	//ImGui::Text("score = %d", score);
}