#pragma once
#include "Framework.h"
#include "PostEffect.h"

// ���̃Q�[���ŗL�̏����N���X
class MyGame : public WristerEngine::Framework
{
private:
	WristerEngine::_2D::PostEffect postEffect;

public:
	// ������(�I�[�o�[���C�h)
	void Initialize();
	// �X�V(�I�[�o�[���C�h)
	void Update();
	// �`��(�I�[�o�[���C�h)
	void Draw();
	// �I������(�I�[�o�[���C�h)
	void Finalize();
};