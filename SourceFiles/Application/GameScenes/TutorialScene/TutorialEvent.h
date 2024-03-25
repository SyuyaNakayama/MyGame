#pragma once
#include "SpriteAnimation.h"
#include <map>

// チュートリアルの説明
class TutorialEvent
{
private:
	static const float TEX_SIZE_Y;
	// チュートリアルの説明UI
	std::map<std::string, std::unique_ptr<WristerEngine::_2D::Sprite>> sprites;
	// チュートリアルの説明番号
	UINT32 phase = 0;
	WristerEngine::_2D::SpriteAnimation enter;

public:
	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Draw();
	// 次のフェーズへ進める
	void NextPhase();
};