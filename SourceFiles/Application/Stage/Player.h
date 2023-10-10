#pragma once
#include "Collider.h"
#include "PlayerCamera.h"
#include "JsonLoader.h"
#include "Timer.h"

class Stage;

class Player : public SphereCollider, public BoxCollider
{
private:
	static const float PLAYER_MOVE_FORCE;
	Object3d* object;
	std::unique_ptr<BaseCamera> camera;
	int isTurn = 0; // falseの時z+の方向に移動、trueの時にz-の方向に移動
	FrameTimer moveTimer = 180;
	Stage* stage = nullptr;

	void Move_Play();
	void Move_Title();
	void (Player::* Move_Title_State)();
	void (Player::* Move)();

public:
	void Initialize(const ObjectData& objectData);
	void SetStage(Stage* stage_) { stage = stage_; }
	void Update();
};