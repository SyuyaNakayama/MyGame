#pragma once
#include "Collider.h"
#include "PlayerCamera.h"
#include "Timer.h"
#include "GameObject.h"

class Stage;

// プレイヤーのオブジェクト
class Player : public SphereCollider, public BoxCollider, public GameObject
{
private:
	static const float PLAYER_MOVE_FORCE;
	Object3d* object;
	std::unique_ptr<BaseCamera> camera;
	int isTurn = 0; // falseの時z+の方向に移動、trueの時にz-の方向に移動
	FrameTimer moveTimer = 180;

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
	void Initialize(const ObjectData& objectData);
	// 更新
	void Update();
};