#include "Stage.h"

const Vector2 Stage::STAGE_SIZE = { 60,100 };

void Stage::SetBlocks()
{
	// 床
	blocks[0].Initialize({ STAGE_SIZE.x + 10,5,STAGE_SIZE.y + 10 }, {}, { 0,1,0 }, 0.0f);
	// ステージを囲う壁
	blocks[1].Initialize({ 5,5,STAGE_SIZE.y }, { STAGE_SIZE.x + 5,10,0 }, { -1,0,0 }, STAGE_SIZE.x); // 右
	blocks[2].Initialize({ 5,5,STAGE_SIZE.y }, { -STAGE_SIZE.x - 5,10,0 }, { 1,0,0 }, STAGE_SIZE.x); // 左
	blocks[3].Initialize({ STAGE_SIZE.x + 10,5,5 }, { 0,10,STAGE_SIZE.y + 5 }, { 0,0,-1 }, STAGE_SIZE.y); // 奥
	blocks[4].Initialize({ STAGE_SIZE.x + 10,5,5 }, { 0,10,-STAGE_SIZE.y - 5 }, { 0,0,1 }, STAGE_SIZE.y); // 前
}

void Stage::Initialize()
{
	SetBlocks();
	player.Initialize();
	for (size_t i = 0; i < 11; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			std::unique_ptr<Object> newObj = std::make_unique<Object>();
			newObj->Initialize({ -50 + 10 * (float)i,5,10 * (float)j });
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
	for (auto& block : blocks) { block.Draw(); }
	player.Draw();
	for (auto& object : objects) { object->Draw(); }
}
