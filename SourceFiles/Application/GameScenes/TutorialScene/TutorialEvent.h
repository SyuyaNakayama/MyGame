#pragma once
#include "Sprite.h"

// チュートリアルの説明
class TutorialEvent
{
private:
	static const float TEX_SIZE_Y;
	// チュートリアルのテキスト画像
	std::unique_ptr<WristerEngine::_2D::Sprite> text;
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