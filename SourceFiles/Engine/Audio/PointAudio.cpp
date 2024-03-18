#include "PointAudio.h"
#include "ModelManager.h"
#include "Camera.h"
#include <cmath>
using namespace WristerEngine;

void PointAudio::Initialize(const std::string& fileName, Vector3 audioPos_, bool useCamera_, bool usePan_)
{
	Audio::Initialize(fileName);
	useCamera = useCamera_;
	audioPos = audioPos_;
	usePan = usePan_;
}

void PointAudio::Update()
{
	if (useCamera)
	{
		_3D::Camera* vp = _3D::ModelManager::GetViewProjection();
		micPos = vp->eye;
		forward = Normalize(vp->target - vp->eye);
	}
	// �}�C�N���特���̋���
	Vector3 toMic = micPos - audioPos;
	float dis = toMic.Length();
	// ������1�������ƁA�����̉��ʂ��傫���Ȃ�̂Œ���
	dis = max(dis, 1.0f);
	// ��������
	float dic = 20.0f * std::log10f(dis); // �f�V�x���̌v�Z��(20 * log10(d)���)
	// dic�ŏ��l
	const float MIN_VOLUME = -10000.0f;
	dic = max(dic, MIN_VOLUME);
	SetVolume(-(long)(dic * 100.0f));
	// �����̍��E�ړ�(�p��)
	if (!usePan) { return; }
	// y��������������2�������ŊO�ς����
	Vector2 dVec[2];
	dVec[0] = { forward.x,forward.z };
	toMic.Normalize();
	dVec[1] = { toMic.x,toMic.z };
	float cross = Cross(dVec[0], dVec[1]);
	SetBalance((long)(cross * (float)panStrength));
}