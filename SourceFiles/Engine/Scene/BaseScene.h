#pragma once
#include "Input.h"
#include "DebugCamera.h"
class SceneManager;

// シーン基底クラス
class BaseScene
{
protected:
	SceneManager* sceneManager = nullptr;
	Input* input = Input::GetInstance();
	DebugCamera debugCamera;

public:
	// コンストラクタ
	BaseScene();
	virtual ~BaseScene() = default;
	// 初期化
	virtual void Initialize() = 0;
	// 更新
	virtual void Update() = 0;
	// 描画
	virtual void Draw() = 0;
	// 終了
	virtual void Finalize() {};
};