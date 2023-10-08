#include "Audio.h"
#include "D3D12Common.h"
#include <fstream>

std::string Audio::DEFAULT_TEXTURE_DIRECTORY_PATH = "Resources/Sounds/";

void Audio::Initialize(const std::string& fileName)
{
	Result result;
	// FilterGraph�𐶐�
	result = CoCreateInstance(CLSID_FilterGraph,
		NULL, CLSCTX_INPROC,
		IID_IGraphBuilder,
		(LPVOID*)&graphBuilder);
	
	// MediaControl�C���^�[�t�F�[�X�擾
	result = graphBuilder->QueryInterface(IID_IMediaControl, (LPVOID*)&mediaControl);
	result = graphBuilder->QueryInterface(IID_IMediaPosition, (LPVOID*)&mediaPosition);
	result = graphBuilder->QueryInterface(IID_IBasicAudio, (LPVOID*)&basicAudio);

	std::string fullPath = DEFAULT_TEXTURE_DIRECTORY_PATH + fileName;

	// ���C�h������ɕϊ������ۂ̕�����o�b�t�@�T�C�Y���v�Z
	int filePathBufferSize = MultiByteToWideChar(CP_ACP, 0, fullPath.c_str(), -1, nullptr, 0);
	// ���C�h������ɕϊ�
	std::vector<wchar_t> wfilePath(filePathBufferSize);
	MultiByteToWideChar(CP_ACP, 0, fullPath.c_str(), -1, wfilePath.data(), filePathBufferSize);
	// Graph�𐶐�
	result = mediaControl->RenderFile((BSTR)wfilePath.data());
}

bool Audio::IsFinished()
{
	double currentTime = 0, duration = 0;
	mediaPosition->get_CurrentPosition(&currentTime);
	mediaPosition->get_Duration(&duration);
	return currentTime == duration;
}