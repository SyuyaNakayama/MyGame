#pragma once
#include <string>
#include <wrl.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <mfapi.h>
#include <dshow.h>
#include <memory>
#include <wrl.h>

namespace WristerEngine
{
	class AudioManager;

	// �I�[�f�B�I
	class Audio
	{
	private:
		Microsoft::WRL::ComPtr<IGraphBuilder> graphBuilder;
		Microsoft::WRL::ComPtr<IMediaControl> mediaControl;
		Microsoft::WRL::ComPtr<IMediaPosition> mediaPosition;
		Microsoft::WRL::ComPtr<IBasicAudio> basicAudio;
		// �f�t�H���g�f�B���N�g��
		static std::string DEFAULT_DIRECTORY_PATH;

		// �Đ����I�������
		bool IsFinished();

	protected:
		// ������
		void Initialize(const std::string& fileName);

	public:
		friend AudioManager;
		// ���z�f�X�g���N�^
		virtual ~Audio() = default;
		// �Đ�
		void Play() { mediaControl->Run(); SetPlayPosition(0); }
		// ���f
		void Stop() { mediaControl->Stop(); }
		// �X�s�[�h�ύX
		void SetSpeed(double playSpd) { mediaPosition->put_Rate(playSpd); }
		// �Đ��ʒu�ύX(�b�P��)
		void SetPlayPosition(double playPosition) { mediaPosition->put_CurrentPosition(playPosition); }
		// -10000(����)~0(�ő剹��) : �P�� �f�V�x��
		void SetVolume(long volume) { basicAudio->put_Volume(volume); }
		// -10000(��)�`10000(�E)
		void SetBalance(long balance) { basicAudio->put_Balance(balance); }
	};
}