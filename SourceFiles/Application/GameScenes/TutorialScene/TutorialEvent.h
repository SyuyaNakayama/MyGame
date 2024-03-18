#pragma once
#include "Sprite.h"
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