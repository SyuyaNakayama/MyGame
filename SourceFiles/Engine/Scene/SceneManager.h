#pragma once
#include "BaseScene.h"
#include "FadeManager.h"
#include "SceneFactory.h"

// シーン管理
class SceneManager final
{
private:
	std::unique_ptr<BaseScene> scene;
	Scene nowScene = Scene::Null;
	Scene nextScene = Scene::Null;
	FadeManager fadeManager;
	AbstractSceneFactory* sceneFactory = SceneFactory::GetInstance();
	bool isObjectClear = false, isParticleClear = false;

	SceneManager() = default;
	~SceneManager() = default;

public:
	SceneManager(const SceneManager& obj) = delete;
	SceneManager& operator=(const SceneManager& obj) = delete;
	// インスタンス取得
	static SceneManager* GetInstance();
	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Draw();
	// 終了
	void Finalize() { scene->Finalize(); }
	// シーン切り替え
	void ChangeScene(Scene nextScene_, bool isObjectClear = true, bool isParticleClear = true, bool isUseFade = true);
	// 現在のシーン取得
	Scene GetNowScene() { return nowScene; }
};