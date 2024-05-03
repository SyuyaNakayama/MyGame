#include "PlayMode.h"
#include "Constant.h"

using namespace WristerEngine::_2D;
using namespace WristerEngine::_3D;

void PlayMode::Initialize()
{
	OperateDrawer::Initialize();

	// �r�b�g�}�b�v�̐ݒ�
	BitMapProp bitMapProp = Const(BitMapProp, "UiScore");
	bitMapProp.fileName = "ui/num.png";

	// �X�R�A
	*scoreSprite.GetBitMapProp() = bitMapProp;
	scoreSprite.Initialize();
	sprites["Score"] = Sprite::Create("ui/score.png", Const(Vector2, "UiScorePosition"), { 0.5f,0.5f });
}

void PlayMode::Update()
{
	// �|�[�Y���j���[�؂�ւ�
	if (OperateConfig::GetInstance()->GetTrigger("Pause"))
	{
		WristerEngine::SceneManager::GetInstance()->Pause();
		return;
	}

	OperateDrawer::Update();
	scoreSprite.Update(stage->GetScore());
}

void PlayMode::Draw()
{
	OperateDrawer::Draw();
	scoreSprite.Draw();
}