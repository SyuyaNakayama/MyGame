#pragma once
#include <string>
#include <wrl.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <mfapi.h>
#include <dshow.h>
#include <memory>
#include <wrl.h>

class AudioManager;

class Audio
{
private:
	Microsoft::WRL::ComPtr<IGraphBuilder> graphBuilder;
	Microsoft::WRL::ComPtr<IMediaControl> mediaControl;
	Microsoft::WRL::ComPtr<IMediaPosition> mediaPosition;
	Microsoft::WRL::ComPtr<IBasicAudio> basicAudio;
	// �f�t�H���g�f�B���N�g��
	static std::string DEFAULT_TEXTURE_DIRECTORY_PATH;
	
	bool IsFinished();

protected:
	void Initialize(const std::string& fileName);

public:
	friend AudioManager;
	virtual ~Audio() = default;
	void Play() { mediaControl->Run(); SetPlayPosition(0); }
	void Stop() { mediaControl->Stop(); }
	void SetSpeed(double playSpd) { mediaPosition->put_Rate(playSpd); }
	void SetPlayPosition(double playPosition) { mediaPosition->put_CurrentPosition(playPosition); }
	// -10000(����)~0(�ő剹��) : �P�� �f�V�x��
	void SetVolume(long volume) { basicAudio->put_Volume(volume); }
	// -10000(��)�`10000(�E)
	void SetBalance(long balance) { basicAudio->put_Balance(balance); }
};