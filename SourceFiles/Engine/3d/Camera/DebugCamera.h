#pragma once
#include "ViewProjection.h"
#include "Quaternion.h"

// �f�o�b�O�J����
class DebugCamera : public ViewProjection
{
private:
	float distance = 50;
	Quaternion rotQ = 1.0f;

public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="targetPos">�����_���W</param>
	/// <param name="distance">�����_���W�܂ł̋���</param>
	void Initialize(Vector3 targetPos = { 0,0,0 }, float distance = 50);
	// �X�V
	void Update();
};