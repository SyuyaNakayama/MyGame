#pragma once
#include "Input.h"
#include "DebugCamera.h"
#include "AbstractUIDrawer.h"
#include <memory>

class SceneManager;

// �V�[�����N���X
class BaseScene
{
protected:
	SceneManager* sceneManager = nullptr;
	Input* input = Input::GetInstance();
	DebugCamera debugCamera;
	std::unique_ptr<AbstractUIDrawer> uiDrawer;

public:
	// �R���X�g���N�^
	BaseScene();
	virtual ~BaseScene() = default;
	// ������
	virtual void Initialize() = 0;
	// �X�V
	virtual void Update() = 0;
	// �`��
	virtual void Draw() { uiDrawer->Draw(); }
	// �I��
	virtual void Finalize() {}
};