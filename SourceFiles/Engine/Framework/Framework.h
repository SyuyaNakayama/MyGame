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
	virtual void Initialize();
	virtual void Finalize();
	virtual void Update();
	virtual void Draw() = 0;
	virtual bool IsEndRequest();
	void Run();
};