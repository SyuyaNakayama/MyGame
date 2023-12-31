#pragma once
#include "SceneManager.h"
#include "DirectXCommon.h"

// ゲーム処理の枠組みクラス
class Framework
{
protected:
	std::wstring windowName;
	WindowsAPI* wAPI = WindowsAPI::GetInstance();
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	Input* input = Input::GetInstance();
	SceneManager* sceneManager = SceneManager::GetInstance();

public:
	virtual ~Framework() = default;
	// 初期化
	virtual void Initialize();
	// 終了
	virtual void Finalize();
	// 更新
	virtual void Update();
	// 描画
	virtual void Draw() = 0;
	// 終了チェック
	virtual bool IsEndRequest();
	// 実行
	void Run();
};