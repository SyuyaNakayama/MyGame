#include "DebugCamera.h"
#include "Input.h"
#include "WindowsAPI.h"

void DebugCamera::Initialize(Vector3 targetPos, float distance_)
{
	distance = distance_;
	target = eye = targetPos;
	eye.z -= distance;
	ViewProjection::Initialize();
}

void DebugCamera::Update()
{
	bool dirty = false;
	Vector2 angle;
	Vector2 scale = { 1.0f / WindowsAPI::WIN_SIZE.x, 1.0f / WindowsAPI::WIN_SIZE.y };
	Input* input = Input::GetInstance();

	// �}�E�X�̓��͂��擾
	Input::MouseMove mouseMove = input->GetMouseMove();

	// �}�E�X�̍��{�^����������Ă�����J��������]������
	if (input->IsInput(Mouse::Left))
	{
		angle = -Vector2((float)mouseMove.lY * scale.x, (float)mouseMove.lX * scale.y) * PI;
		dirty = true;
	}

	// �}�E�X�̒��{�^����������Ă�����J�����𕽍s�ړ�������
	if (input->IsInput(Mouse::Middle))
	{
		Vector3 move = Vector3(-(float)mouseMove.lX, (float)mouseMove.lY) / 75.0f;
		move = Quaternion::RotateVector(move, rotQ);

		CameraMove(move);
		dirty = true;
	}

	// �z�C�[�����͂ŋ�����ύX
	if (mouseMove.lZ != 0)
	{
		distance -= mouseMove.lZ / 50.0f;
		distance = max(distance, 1.0f);
		dirty = true;
	}

	if (!dirty) { return; }
	// �ǉ���]����Quaternion�𐶐�
	Quaternion rotQNew;
	rotQNew = Quaternion::MakeAxisAngle(Vector3::MakeAxis(Axis::Y), -angle.y);
	rotQNew *= Quaternion::MakeAxisAngle(Vector3::MakeAxis(Axis::X), -angle.x);

	// �ݐς�Quaternion������
	rotQ *= rotQNew;

	// �����_���王�_�ւ̃x�N�g���ƁA������x�N�g��
	Vector3 vTargetEye = { 0.0f, 0.0f, -distance };
	Vector3 vUp = { 0.0f, 1.0f };

	// �x�N�g������]
	vTargetEye = Quaternion::RotateVector(vTargetEye, rotQ);
	vUp = Quaternion::RotateVector(vUp, rotQ);

	// �����_���炸�炵���ʒu�Ɏ��_���W������
	eye = target + vTargetEye;
	up = vUp;
}