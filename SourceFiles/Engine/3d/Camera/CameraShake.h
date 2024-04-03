#pragma once
#include "Easing.h"
#include "Random.h"
#include "Vector.h"
#include <unordered_map>

namespace WristerEngine::_3D
{
	class CameraShake
	{
	private:
		Easing easing; // �C�[�W���O�ɂ��V�F�C�N�͈͂̌���
		bool isWhile = false; // �V�F�C�N����
		std::unordered_map<Axis, Random_Float> rand{}; // ����

	public:
		// �V�F�C�N���
		struct Prop
		{
			Vector3 range; // �V�F�C�N�͈̔�
			int time; // �V�F�C�N����
			Easing::Type easingType; // �V�F�C�N�����C�[�W���O
		};

		/// <summary>
		/// �C���X�^���X����
		/// </summary>
		/// <param name="shakeProp">�V�F�C�N���</param>
		/// <returns>CameraShake�̃C���X�^���X</returns>
		static std::unique_ptr<CameraShake> Create(const Prop& shakeProp);

		/// <summary>
		/// �V�F�C�N�͈̔͂��Đݒ�
		/// </summary>
		/// <param name="shakeRange_">�V�F�C�N�͈̔�</param>
		void SetShakeRange(const Vector3& shakeRange_);

		// �V�F�C�N�J�n
		void Start();

		/// <summary>
		/// �X�V����
		/// </summary>
		/// <returns>�V�F�C�N�̒l</returns>
		Vector3 Update();
	};
}