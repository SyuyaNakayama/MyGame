#pragma once
#include "SpriteAnimation.h"
#include <map>
#include "Constant.h"

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
	WristerEngine::Constant* constant = WristerEngine::Constant::GetInstance();

	// エンターキー押したときのイベントの切り替え
	void (TutorialEvent::*EnterEvent)() = nullptr;
	void EnterEventManager();

	// ヒント表示切り替え
	void PrintFlip();

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