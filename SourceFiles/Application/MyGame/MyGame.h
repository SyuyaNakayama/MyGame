#pragma once
#include "Framework.h"
#include "PostEffect.h"
#include "ParticleManager.h"

// このゲーム固有の処理クラス
class MyGame : public Framework
{
private:
	std::unique_ptr<PostEffect> postEffect;

public:
	// 初期化(オーバーライド)
	void Initialize();
	// 更新(オーバーライド)
	void Update();
	// 描画(オーバーライド)
	void Draw();
	// 終了処理(オーバーライド)
	void Finalize();
};