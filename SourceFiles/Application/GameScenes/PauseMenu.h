#pragma once
#include "BasePauseMenu.h"
#include "OperateConfig.h"

// 設定項目基底クラス
class BaseItem : public WristerEngine::_2D::AbstractUIDrawer
{
protected:
	OperateConfig* operateConfig = OperateConfig::GetInstance();
	float param = 0; // PauseMenuクラスに渡す調整項目の値
	float uiMoveDis = 0; // UIのLeftTop.x移動距離
	WristerEngine::Easing animation; // アニメーションに使うイージング
	float ltMemX = 0; // LeftTop.x記憶変数
	float posY = 0; // 表示する場所(Y軸成分)
	std::string spriteIndexName; // スプライトの配列の添え字の名前

	// 操作切り替えの関数
	void (BaseItem::* State)() = &BaseItem::Idle;

public:
	virtual ~BaseItem() = default;
	// AbstractUIDrawer を介して継承されました
	virtual void Initialize() override;
	void Update() override;
	void Draw() override { AbstractUIDrawer::Draw(); }

	void SpriteMove(); // スプライトアニメーション
	virtual void Idle() = 0; // 操作待機中
	void IdleAction(float uiMoveDis); // 左右キー入力時の挙動

	// posYを設定
	void SetPosY(float posY_) { posY = posY_; }

	// 調整項目の値を返す
	float GetParam() const { return param; }
};

class CameraModeItem : public BaseItem
{
	void Idle(); // 操作待機中

	void Initialize() override;
};

class Spd_DisItem : public BaseItem
{
	float paramVal = 5.0f;

	void Idle(); // 操作待機中

	// パラメーター値を計算する
	float CalcParam() const { return 0.2f * paramVal; }

	void Initialize() override;
};

// カメラの調整項目
struct CameraParam
{
	float moveSpd = 0, dis = 0;
};

class PauseMenu final : public WristerEngine::BasePauseMenu
{
	OperateConfig* operateConfig = OperateConfig::GetInstance();
	std::map<std::string, std::unique_ptr<BaseItem>> items; // 設定項目
	CameraParam param;

	// 項目の選択
	int select = 0;
	std::vector<std::string> SELECT_STR = { "Rot","Spd","Dis" };

	PauseMenu() = default;
	~PauseMenu() = default;

public:
	PauseMenu(const PauseMenu& obj) = delete;
	const PauseMenu& operator=(const PauseMenu& obj) = delete;

	// インスタンス取得
	static PauseMenu* GetInstance();

	// BasePauseMenu を介して継承されました
	void Initialize() override;
	void Update() override;
	void Draw() override;

	// CameraParamを取得
	const CameraParam& GetCameraParam() const { return param; }
};