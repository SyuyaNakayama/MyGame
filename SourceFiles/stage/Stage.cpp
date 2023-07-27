#include "Stage.h"
#include <imgui.h>

const Vector2 Stage::STAGE_SIZE = { 75,75 };
int Stage::score = 0;

void Stage::Initialize()
{
	levelData = JsonLoader::LoadJson("stage");
	for (auto& objectData : levelData->objects)
	{
		if (objectData.fileName == "cube")
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
	}
}

void Stage::Update()
{
	player.Update();
	objects.remove_if([](std::unique_ptr<Object>& object) { return object->IsDestroy(); });
	for (auto& object : objects) { object->Update(); }
	for (auto& goal : goals) { goal->Update(); }
	//ImGui::Text("score = %d", score);
}

void Stage::Draw()
{
	for (auto& block : blocks) { block->Draw(); }
	player.Draw();
	for (auto& object : objects) { object->Draw(); }
	for (auto& goal : goals) { goal->Draw(); }
}
