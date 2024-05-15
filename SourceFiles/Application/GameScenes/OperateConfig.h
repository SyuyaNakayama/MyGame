#pragma once
#include "Input.h"
#include "Constant.h"
#include <Sprite.h>

// ゲームの操作を管理するクラス
class OperateConfig final
{
private:
	WristerEngine::Input* input = WristerEngine::Input::GetInstance();
	WristerEngine::Constant* constant = WristerEngine::Constant::GetInstance();

	OperateConfig() = default;
	~OperateConfig() = default;

	std::unique_ptr<WristerEngine::_2D::Sprite> LoadSprite(const std::string& str);

public:
	OperateConfig(const OperateConfig& obj) = delete;
	OperateConfig operator=(const OperateConfig& obj) = delete;

	/// <summary>
	/// インスタンス取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static OperateConfig* GetInstance();

	/// <summary>
	/// 操作キーが押されたかを取得
	/// </summary>
	/// <param name="str">操作キー</param>
	/// <returns>操作キーが押されたか</returns>
	bool GetPush(const std::string& str);

	/// <summary>
	/// 操作キーが押された瞬間かを取得
	/// </summary>
	/// <param name="str">操作キー</param>
	/// <returns>操作キーが押された瞬間か</returns>
	bool GetTrigger(const std::string& str);

	/// <summary>
	/// 操作キーのUIを生成
	/// </summary>
	/// <param name="str">操作キー</param>
	/// <returns>操作キーのSpriteインスタンス(unique_ptr)</returns>
	std::unique_ptr<WristerEngine::_2D::Sprite> CreateOperateSprite(const std::string& str);
	
	std::unique_ptr<WristerEngine::_2D::Sprite> CreateOperateSpriteAnimation(const std::string& str);
};