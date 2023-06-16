#include "Stage.h"

const Vector2 Stage::STAGE_SIZE = { 60,100 };

void Stage::SetBlocks()
{
	// 床
	blocks[0].Initialize({ STAGE_SIZE.x + 10,5,STAGE_SIZE.y + 10 }, {});
	// ステージを囲う壁
	blocks[1].Initialize({ 5,5,STAGE_SIZE.y }, { STAGE_SIZE.x + 5,10,0 });
	blocks[2].Initialize({ 5,5,STAGE_SIZE.y }, { -STAGE_SIZE.x - 5,10,0 });
	blocks[3].Initialize({ STAGE_SIZE.x + 10,5,5 }, { 0,10,STAGE_SIZE.y + 5 });
	blocks[4].Initialize({ STAGE_SIZE.x + 10,5,5 }, { 0,10,-STAGE_SIZE.y - 5 });
}

void Stage::Initialize()
{
	SetBlocks();
	player.Initialize();
	for (auto& object : objects) { object.Initialize(); }
}

void Stage::Update()
{
	player.Update();
	for (auto& object : objects) { object.Update(); }
}

void Stage::Draw()
{
	for (auto& block : blocks) { block.Draw(); }
	player.Draw();
	for (auto& object : objects) { object.Draw(); }
}
