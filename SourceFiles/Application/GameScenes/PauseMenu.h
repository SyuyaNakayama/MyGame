#pragma once
#include "BasePauseMenu.h"
#include "OperateConfig.h"

// �ݒ荀�ڊ��N���X
class BaseItem : public WristerEngine::_2D::AbstractUIDrawer
{
protected:
	OperateConfig* operateConfig = OperateConfig::GetInstance();
	float param = 0; // PauseMenu�N���X�ɓn���������ڂ̒l
	float uiMoveDis = 0; // UI��LeftTop.x�ړ�����
	WristerEngine::Easing animation; // �A�j���[�V�����Ɏg���C�[�W���O
	float ltMemX = 0; // LeftTop.x�L���ϐ�
	float posY = 0; // �\������ꏊ(Y������)

	// ����؂�ւ��̊֐�
	void (BaseItem::* State)() = &BaseItem::Idle;

public:
	virtual ~BaseItem() = default;
	// AbstractUIDrawer ����Čp������܂���
	virtual void Initialize() override;
	void Update() override;
	void Draw() override { AbstractUIDrawer::Draw(); }
	
	virtual void SpriteMove() = 0; // �X�v���C�g�A�j���[�V����
	virtual void Idle() = 0; // ����ҋ@��
	virtual void IdleAction(float uiMoveDis) = 0; // ���E�L�[���͎��̋���

	// posY��ݒ�
	void SetPosY(float posY_) { posY = posY_; }

	// �������ڂ̒l��Ԃ�
	float GetParam() const { return param; }
};

class CameraModeItem : public BaseItem
{
	void SpriteMove(); // �X�v���C�g�A�j���[�V����
	void Idle(); // ����ҋ@��
	void IdleAction(float uiMoveDis); // ���E�L�[���͎��̋���

	void Initialize() override;
};

class Spd_DisItem : public BaseItem
{
	float paramVal = 5.0f;

	void SpriteMove(); // �X�v���C�g�A�j���[�V����
	void Idle(); // ����ҋ@��
	void IdleAction(float uiMoveDis); // ���E�L�[���͎��̋���

	void Initialize() override;
};

// �J�����̒�������
struct CameraParam
{
	float moveSpd = 0, dis = 0;
};

class PauseMenu final : public WristerEngine::BasePauseMenu
{
	OperateConfig* operateConfig = OperateConfig::GetInstance();
	std::map<std::string, std::unique_ptr<BaseItem>> items; // �ݒ荀��
	CameraParam param;

	PauseMenu() = default;
	~PauseMenu() = default;

public:
	PauseMenu(const PauseMenu& obj) = delete;
	const PauseMenu& operator=(const PauseMenu& obj) = delete;

	// �C���X�^���X�擾
	static PauseMenu* GetInstance();

	// BasePauseMenu ����Čp������܂���
	void Initialize() override;
	void Update() override;
	void Draw() override;

	// CameraParam���擾
	const CameraParam& GetCameraParam() const { return param; }
};