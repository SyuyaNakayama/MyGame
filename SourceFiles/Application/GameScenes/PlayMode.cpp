#include "PlayMode.h"
#include "Constant.h"

using namespace WristerEngine::_2D;
using namespace WristerEngine::_3D;

void PlayMode::Initialize()
{
	OperateDrawer::Initialize();
	WristerEngine::Constant* constant = WristerEngine::Constant::GetInstance();

	// �r�b�g�}�b�v�̐ݒ�
	BitMapProp bitMapProp = constant->GetConstant<BitMapProp>("uiScore");
	bitMapProp.fileName = "ui/num.png";

	// �X�R�A
	*scoreSprite.GetBitMapProp() = bitMapProp;
	scoreSprite.Initialize();
	uiScore = Sprite::Create("ui/score.png");
	uiScore->SetCenterAnchor();
	uiScore->position = constant->GetConstant<Vector2>("uiScorePosition");
	uiScore->Update();
}

void PlayMode::Update()
{
	OperateDrawer::Update();
	scoreSprite.Update(stage->GetScore());
}

void PlayMode::Draw()
{
	OperateDrawer::Draw();
	scoreSprite.Draw();
	uiScore->Draw();
}