#pragma once
#include "Collider.h"
#include "PlayerCamera.h"
#include "JsonLoader.h"
#include "Timer.h"

class Player : public SphereCollider, public BoxCollider
{
private:
	static const float PLAYER_MOVE_FORCE;
	Object3d* object;
	std::unique_ptr<BaseCamera> camera;
	int isTurn = 0; // false‚Ìz+‚Ì•ûŒü‚ÉˆÚ“®Atrue‚Ì‚Éz-‚Ì•ûŒü‚ÉˆÚ“®
	FrameTimer moveTimer = 180;

	void Move_Play();
	void Move_Title();
	void (Player::* Move_Title_State)();
	void (Player::* Move)();

public:
	void Initialize(const ObjectData& objectData);
	void Update();
};