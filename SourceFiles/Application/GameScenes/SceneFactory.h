#pragma once
#include "AbstractSceneFactory.h"

// 各シーンの生成クラス
class SceneFactory : public AbstractSceneFactory
{
private:
	SceneFactory() = default;

public:
	// コンストラクタ
	SceneFactory(const SceneFactory& obj) = delete;
	// インスタンス取得
	static SceneFactory* GetInstance();

	/// <summary>
	/// シーン作成
	/// </summary>
	/// <param name="scene">次に作るシーン</param>
	/// <returns>作成されたクラスのポインタ</returns>
	BaseScene* CreateScene(Scene scene) override;
};