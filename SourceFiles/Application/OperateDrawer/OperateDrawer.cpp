#include "OperateDrawer.h"
#include "Constant.h"

using namespace WristerEngine::_2D;

void OperateDrawer::Initialize()
{
	WristerEngine::Constant* constant = WristerEngine::Constant::GetInstance();

	frame = Sprite::Create("UI/uiFrame.png");
	frame->position = constant->GetConstant<Vector2>("OperateFramePos");
	frame->size = constant->GetConstant<Vector2>("OperateFrameSize");
	frame->Update();
	using Key = WristerEngine::Key;

	// ‘€ìƒL[‚Ì‰æ‘œ‚Ì“Ç‚İ‚İ‚ÆˆÊ’u’²®
	mapChip = std::make_unique<MapChip>();
	mapChip->Initialize(Const(Vector2, "ChipLTPos"), Const(Vector2, "ChipSize"), Const(Vector2, "ChipAnchor"));
	mapChip->AddSprite("UI/Key/key_A.png", { 0,1 });
	mapChip->AddSprite("UI/Key/key_D.png", { 2,1 });
	mapChip->AddSprite("UI/Key/key_W.png", { 1,0 });
	mapChip->AddSprite("UI/Key/key_S.png", { 1,1 });
	mapChip->AddSprite("UI/Key/key_Left.png", { 0,3 });
	mapChip->AddSprite("UI/Key/key_Right.png", { 2,3 });
	mapChip->AddSprite("UI/Key/key_Up.png", { 1,2 });
	mapChip->AddSprite("UI/Key/key_Down.png", { 1,3 });
	mapChip->AddSprite("UI/Key/key_SHIFT.png", { 0,4 });

	operateUI["player"] = Sprite::Create("UI/Move.png");
	operateUI["player"]->anchorPoint.y = 0.25f;
	//operateUI["player"]->position = { keyUI[Key::D]->position.x, keyUI[Key::W]->position.y };
	//operateUI["player"]->position += { keyUI[Key::D]->size.x, Half(keyUI[Key::D]->size.y) };

	operateUI["camera"] = Sprite::Create("UI/Camera.png");
	operateUI["camera"]->anchorPoint.y = 0.25f;
	//operateUI["camera"]->position = { keyUI[Key::Right]->position.x, keyUI[Key::Up]->position.y };
	//operateUI["camera"]->position += { keyUI[Key::D]->size.x, Half(keyUI[Key::D]->size.y) };

	operateUI["dash"] = Sprite::Create("UI/Dash.png");
	operateUI["dash"]->anchorPoint.y = 0.5f;
	//operateUI["dash"]->position = keyUI[Key::Rshift]->position;
	//operateUI["dash"]->position.x += Half(keyUI[Key::Rshift]->size.x);

	for (auto& s : operateUI) { s.second->Update(); }
}

void OperateDrawer::Update()
{
	mapChip->Update();
}

void OperateDrawer::Draw()
{
	frame->Draw();
	for (auto& s : operateUI) { s.second->Draw(); }
	mapChip->Draw();
}