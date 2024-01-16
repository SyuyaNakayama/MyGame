#pragma once
#include "Collider.h"
#include "PlayerCamera.h"
#include "Timer.h"
#include "GameObject.h"

class Stage;

// プレイヤーのオブジェクト
class Player : public WristerEngine::SphereCollider, public WristerEngine::BoxCollider, public WristerEngine::_3D::GameObject
{
private:
	static const float PLAYER_MOVE_FORCE;
	WristerEngine::_3D::Object3d* object;
	std::unique_ptr<WristerEngine::_3D::BaseCamera> camera;
	int isTurn = 0; // falseの時z+の方向に移動、trueの時にz-の方向に移動
	WristerEngine::FrameTimer moveTimer = 180;

	// プレイシーンでの動き
	void Move_Play();
	// タイトルシーンでの動き
	void Move_Title();
	// タイトルシーンでの移動のステートパターン
	void (Player::* Move_Title_State)();
	// プレイシーンでの移動のステートパターン
	void (Player::* Move)();

public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="objectData">Jsonファイルから読み込んだデータ</param>
	void Initialize(const WristerEngine::ObjectData& objectData);
	// 更新
	void Update();
};