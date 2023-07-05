#include "Stage.h"

const Vector2 Stage::STAGE_SIZE = { 75,75 };

void Stage::Initialize()
{
	levelData = JsonLoader::LoadJson("stage");
	for (auto& objectData : levelData->objects)
	{
		std::unique_ptr<Block> newBlock = std::make_unique<Block>();
		Vector3 normal;
		newBlock->Initialize(objectData);
		blocks.push_back(std::move(newBlock));
	}
	player.Initialize();
	for (size_t i = 0; i < 9; i++)
	{
		for (size_t j = 0; j < 9; j++)
		{
			std::unique_ptr<Object> newObj = std::make_unique<Object>();
			newObj->Initialize({ -40 + 10 * (float)i,5,8 * (float)j });
			objects.push_back(std::move(newObj));
		}
	}
}

void Stage::Update()
{
	player.Update();
	for (auto& object : objects) { object->Update(); }
}

void Stage::Draw()
{
	for (auto& block : blocks) { block->Draw(); }
	player.Draw();
	for (auto& object : objects) { object->Draw(); }
}
