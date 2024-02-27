#pragma once
#include "OperateDrawer.h"
#include "Stage.h"
#include "BitMapNumber.h"

// �`���[�g���A���ƃv���C�V�[���ŋ��L���Ă������
class PlayMode : public OperateDrawer
{
private:
	std::unique_ptr<WristerEngine::_2D::Sprite> uiScore;
	WristerEngine::_2D::BitMapNumber scoreSprite;

protected:
	Stage* stage;

	// ������(�I�[�o�[���C�h)
	void Initialize();
	// �X�V(�I�[�o�[���C�h)
	void Update();
	// �`��(�I�[�o�[���C�h)
	void Draw();
};