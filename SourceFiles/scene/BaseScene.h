#pragma once
#include "Input.h"
#include "DebugCamera.h"
class SceneManager;

class BaseScene
{
protected:
	SceneManager* sceneManager = nullptr;
	Input* input = Input::GetInstance();
	DebugCamera debugCamera;

public:
	BaseScene();
	virtual ~BaseScene() = default;
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Finalize() {};
};