#pragma once
#include "BasePauseMenu.h"
#include "OperateConfig.h"

// 設定項目基底クラス
class BaseItem : public WristerEngine::_2D::AbstractUIDrawer
{
protected:
	OperateConfig* operateConfig = OperateConfig::GetInstance();
	float param = 0; // PauseMenuクラスに渡す調整項目の値

public:
	virtual ~BaseItem() = default;
	// AbstractUIDrawer を介して継承されました
	virtual void Initialize() override;
	virtual void Update() override { for (auto& s : sprites) { s.second->Draw(); } }
	void Draw() override { for (auto& s : sprites) { s.second->Draw(); } }
	// 調整項目の値を返す
	float GetParam() const { return param; }
};

class CameraModeItem : public BaseItem
{
	float uiMoveDis = 0; // UIのLeftTop.x移動距離
	WristerEngine::Easing animation; // アニメーションに使うイージング
	float ltMemX = 0; // LeftTop.x記憶変数

	// 操作切り替えの関数
	void (CameraModeItem::* State)() = &CameraModeItem::Idle;
	void SpriteMove(); // スプライトアニメーション
	void Idle(); // 操作待機中
	void IdleAction(float uiMoveDis); // 左右キー入力時の挙動

	void Initialize() override;
	void Update() override;
};

//class Spd_DisItem : public BaseItem
//{
//	float uiMoveDis = 0; // UIのLeftTop.x移動距離
//	WristerEngine::Easing animation; // アニメーションに使うイージング
//	float ltMemX = 0; // LeftTop.x記憶変数
//
//	// 操作切り替えの関数
//	void (CameraModeItem::* State)() = &CameraModeItem::Idle;
//	void SpriteMove(); // スプライトアニメーション
//	void Idle(); // 操作待機中
//	void IdleAction(float uiMoveDis); // 左右キー入力時の挙動
//
//	void Initialize() override;
//	void Update() override;
//};

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