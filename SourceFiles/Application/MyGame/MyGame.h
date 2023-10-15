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
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Finalize() override;
};