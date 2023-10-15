#pragma once
#include "Collider.h"
#include "PlayerCamera.h"
#include "Timer.h"
#include "GameObject.h"

class Stage;

// �v���C���[�̃I�u�W�F�N�g
class Player : public SphereCollider, public BoxCollider, public GameObject
{
private:
	static const float PLAYER_MOVE_FORCE;
	Object3d* object;
	std::unique_ptr<BaseCamera> camera;
	int isTurn = 0; // false�̎�z+�̕����Ɉړ��Atrue�̎���z-�̕����Ɉړ�
	FrameTimer moveTimer = 180;

	// �v���C�V�[���ł̓���
	void Move_Play();
	// �^�C�g���V�[���ł̓���
	void Move_Title();
	// �^�C�g���V�[���ł̈ړ��̃X�e�[�g�p�^�[��
	void (Player::* Move_Title_State)();
	// �v���C�V�[���ł̈ړ��̃X�e�[�g�p�^�[��
	void (Player::* Move)();

public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="objectData">Json�t�@�C������ǂݍ��񂾃f�[�^</param>
	void Initialize(const ObjectData& objectData);
	// �X�V
	void Update();
};