#include "Audio.h"
#include "D3D12Common.h"
#include <fstream>
#include <cassert>

void Audio::StaticInitialize()
{
	// COM��������
	Result result = CoInitialize(NULL);
}

void Audio::Initialize(const std::wstring& fileName)
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

	std::wstring fullpath = L"Resources/audios/" + fileName;
	// Graph�𐶐�
	result = mediaControl->RenderFile((BSTR)fullpath.c_str());
}

void Audio::Finalize()
{
	CoUninitialize(); // COM�I��
}