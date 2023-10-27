#pragma once
#include "AbstractSceneFactory.h"

// 各シーンの生成クラス
class SceneFactory : public AbstractSceneFactory
{
private:
	// コンストラクタを
	SceneFactory() = default;
	~SceneFactory() = default;

public:
	SceneFactory(const SceneFactory& obj) = delete;
	SceneFactory& operator=(const SceneFactory& obj) = delete;
	// インスタンス取得
	static SceneFactory* GetInstance();

	/// <summary>
	/// シーン作成
	/// </summary>
	/// <param name="scene">次に作るシーン</param>
	/// <returns>作成されたクラスのポインタ</returns>
	std::unique_ptr<BaseScene> CreateScene(Scene scene) override;
};