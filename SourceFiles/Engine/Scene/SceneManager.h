#pragma once
#include "BaseScene.h"
#include "FadeManager.h"
#include "SceneFactory.h"

// シーン管理
class SceneManager final
{
private:
	BaseScene* scene_ = nullptr;
	Scene nowScene_ = Scene::Null;
	Scene nextScene_ = Scene::Null;
	FadeManager fadeManager_;
	AbstractSceneFactory* sceneFactory_ = SceneFactory::GetInstance();

	SceneManager() = default;
public:
	SceneManager(const SceneManager& obj) = delete;
	// インスタンス取得
	static SceneManager* GetInstance();
	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Draw();
	// 終了
	void Finalize() { scene_->Finalize(); delete scene_; }
	// シーン切り替え
	void ChangeScene(Scene nextScene, bool isUseFade = true);
	// 現在のシーン取得
	Scene GetNowScene() { return nowScene_; }
};