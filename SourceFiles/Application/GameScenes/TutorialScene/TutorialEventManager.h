#pragma once
#include "TutorialEvent.h"

// チュートリアルの説明のマネージャークラス
class TutorialEventManager
{
private:
	// コンストラクタなどをprivateに
	TutorialEventManager() = default;
	~TutorialEventManager() = default;

	TutorialEvent tutorialEvent;
	bool isNext = false;

public:
	TutorialEventManager(const TutorialEventManager& obj) = delete;
	TutorialEventManager& operator=(const TutorialEventManager& obj) = delete;
	// インスタンス取得
	static TutorialEventManager* GetInstance();

	// 初期化
	void Initialize() { tutorialEvent.Initialize(); }
	// 更新
	void Update();
	// 描画
	void Draw();
	// 次のフェーズへ進める
	void NextPhase() { isNext = true; }
};