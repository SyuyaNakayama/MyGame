#pragma once
#include "Input.h"
#include "DebugCamera.h"
#include "AbstractUIDrawer.h"
#include <memory>

class SceneManager;

// シーン基底クラス
class BaseScene
{
protected:
	SceneManager* sceneManager = nullptr;
	Input* input = Input::GetInstance();
	DebugCamera debugCamera;
	std::unique_ptr<AbstractUIDrawer> uiDrawer;

public:
	// コンストラクタ
	BaseScene();
	virtual ~BaseScene() = default;
	// 初期化
	virtual void Initialize() = 0;
	// 更新
	virtual void Update() = 0;
	// 描画
	virtual void Draw() { uiDrawer->Draw(); }
	// 終了
	virtual void Finalize() {}
};