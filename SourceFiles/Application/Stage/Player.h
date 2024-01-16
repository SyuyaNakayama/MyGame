#pragma once
#include "Collider.h"
#include "PlayerCamera.h"
#include "Timer.h"
#include "GameObject.h"

class Stage;

// �v���C���[�̃I�u�W�F�N�g
class Player : public WristerEngine::SphereCollider, public WristerEngine::BoxCollider, public WristerEngine::_3D::GameObject
{
private:
	static const float PLAYER_MOVE_FORCE;
	WristerEngine::_3D::Object3d* object;
	std::unique_ptr<WristerEngine::_3D::BaseCamera> camera;
	int isTurn = 0; // false�̎�z+�̕����Ɉړ��Atrue�̎���z-�̕����Ɉړ�
	WristerEngine::FrameTimer moveTimer = 180;

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
	void Initialize(const WristerEngine::ObjectData& objectData);
	// �X�V
	void Update();
};