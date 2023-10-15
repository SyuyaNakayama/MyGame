#pragma once
#include "Framework.h"
#include "PostEffect.h"
#include "ParticleManager.h"

// ���̃Q�[���ŗL�̏����N���X
class MyGame : public Framework
{
private:
	std::unique_ptr<PostEffect> postEffect;

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