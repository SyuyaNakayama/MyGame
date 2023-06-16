#include "Jump.h"
#include "Input.h"
#include <imgui.h>

void Jump::Start(float jumpV0)
{
	if (isJump) { return; }
	jumpSpd = jumpV0;
	isJump = true;
	collisionAttribute = CollisionAttribute::Player;
	collisionMask = CollisionMask::PlayerJump;
}

void Jump::Update()
{
	worldTransform = *pwt;
	if (!isJump) { return; }
	pwt->translation.y += jumpSpd;
	pwt->Update();
	jumpSpd -= gravity;
	// �������x�̏��
	if (jumpSpd < 0) { jumpSpd = max(-2.0f, jumpSpd); }
}

// �����̐^���̒n�ʂ����o
void Jump::OnCollision(BoxCollider* collider)
{
	// ����R���C�_�[�̏���y���W���擾
	float pairPosY = collider->GetWorldPosition().y + collider->GetRadius3D().y;
	// �����W�Ƒ�����W��y���̍����v�Z
	float disY = std::abs(pwt->translation.y - pairPosY);
	// ���ꂪ������y�������̔��a�����Ȃ璅�n���Ă���
	if (pwt->scale.y >= disY)
	{
		// �����Ă��Ԃ���Ȃ���Ζ���
		if (jumpSpd >= 0 || !isJump) { return; }
		// �W�����v��ԉ���
		pwt->translation.y = pairPosY + 1.0f;
		isJump = false;
	}
	else { Start(0); }
}
