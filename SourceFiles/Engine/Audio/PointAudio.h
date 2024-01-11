#pragma once
#include "Audio.h"
#include "Vector.h"

namespace WristerEngine
{
	// �_���� �}�C�N�Ƃ̈ʒu�֌W�ŉ����ς��
	class PointAudio : public Audio
	{
	private:
		Vector3 audioPos;
		Vector3 micPos;
		Vector3 forward;
		bool useCamera = true;
		bool usePan = true;
		float sPressRate = 1.0f; // ���ȂƂ̉����̔䗦
		long panStrength = 2500; // �p���̋���(�傫���قǍ��E�̉��ʍ����傫���Ȃ�)

		void Initialize(const std::string& fileName, Vector3 audioPos, bool useCamera, bool usePan);
		void Update();

	public:
		friend AudioManager;
		void SetAudioPos(Vector3 pos) { audioPos = pos; }
		void SetMicPos(Vector3 pos) { micPos = pos; }
		void SetForward(Vector3 forward_) { forward = forward_; }
		void SetPanStrength(long panStrength_) { panStrength = panStrength_; }
	};
}