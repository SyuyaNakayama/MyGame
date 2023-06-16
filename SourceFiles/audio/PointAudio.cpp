#include "PointAudio.h"
#include "Model.h"
#include <cmath>

void PointAudio::Initialize(const std::wstring& fileName, Vector3 audioPos_, bool useCamera_, bool usePan_)
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
		ViewProjection* vp = Model::GetViewProjection();
		micPos = vp->eye;
		forward = Normalize(vp->target - vp->eye);
	}
	// �}�C�N���特���̋���
	Vector3 toMic = micPos - audioPos;
	float dis = toMic.Length();
	// ������1�������ƁA�����̉��ʂ��傫���Ȃ�̂Œ���
	if (dis < 1.0f) { dis = 1.0f; }
	// ��������
	float dic = 20.0f * std::log10f(dis);
	if (dic <= -10000) { dic = -10000.0f; }
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