#pragma once
#include "BaseScene.h"
#include "RankAnimation.h"

// 結果発表シーンの処理
class ResultScene : public BaseScene
{
	// 初期化(オーバーライド)
	void Initialize();
	// 更新(オーバーライド)
	void Update();
	// 描画(オーバーライド)
	void Draw();
};


// UI描画クラス(リザルトシーン用)
class UIDrawerResultScene : public AbstractUIDrawer
{
private:
	ScoreGauge scoreGauge; 
	RankAnimation rankAnimation;

public:
	// 初期化(オーバーライド)
	void Initialize();
	// 更新(オーバーライド)
	void Update();
	// 描画(オーバーライド)
	void Draw();
};