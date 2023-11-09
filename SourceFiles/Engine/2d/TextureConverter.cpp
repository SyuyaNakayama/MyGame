#include "TextureConverter.h"
#include <Windows.h>
#include <vector>

using namespace DirectX;

void TextureConverter::LoadWICTextureFromFile(const std::string& filePath)
{
	// �t�@�C���p�X�����C�h������ɕϊ�����
	std::wstring wfilePath = ConvertMultiByteStringToWideString(filePath);

	// �t�H���_�p�X�ƃt�@�C�����𕪗�����
	SeparateFilePath(wfilePath);

	HRESULT result = S_OK;

	if (fileExt == L"dds")
	{
		// DDS�e�N�X�`���̃��[�h
		result = LoadFromDDSFile(wfilePath.c_str(), DDS_FLAGS_NONE, &metadata, scratchImage);
	}
	else
	{
		// WIC�e�N�X�`���̃��[�h
		result = LoadFromWICFile(wfilePath.c_str(), WIC_FLAGS_NONE, &metadata, scratchImage);
	}

	assert(SUCCEEDED(result));
}

std::wstring TextureConverter::ConvertMultiByteStringToWideString(const std::string& mString)
{
	// ���C�h������ɕϊ������ۂ̕�����o�b�t�@�T�C�Y���v�Z
	int filePathBufferSize = MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, nullptr, 0);

	// ���C�h������
	std::wstring wString;
	wString.resize(filePathBufferSize);

	// ���C�h������ɕϊ�
	MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, &wString[0], filePathBufferSize);

	return wString;
}

void TextureConverter::SeparateFilePath(const std::wstring& filePath_)
{
	size_t pos1;
	std::wstring exceptExt;

	// ��؂蕶��'.'���o�Ă����ԍŌ�̕���������
	pos1 = filePath_.rfind('.');
	// �������q�b�g������
	if (pos1 != std::wstring::npos)
	{
		// ��؂蕶���̌����t�@�C���g���q�Ƃ��ĕۑ� 
		fileExt = filePath_.substr(pos1 + 1, filePath_.size() - pos1 - 1);
		// ��؂蕶���̑O�܂ł𔲂��o��
		exceptExt = filePath_.substr(0, pos1);
	}
	else
	{
		fileExt = L"";
		exceptExt = filePath_;
	}

	// ��؂蕶��'\\'���o�Ă����ԍŌ�̕���������
	pos1 = exceptExt.rfind('\\');
	if (pos1 != std::wstring::npos)
	{
		// ��؂蕶���̑O�܂ł��f�B���N�g���p�X�Ƃ��ĕۑ�
		directoryPath = exceptExt.substr(0, pos1 + 1);
		// ��؂蕶���̌����t�@�C�����Ƃ��ĕۑ�
		fileName = exceptExt.substr(pos1 + 1, filePath_.size() - pos1 - 1);
		return;
	}
	// ��؂蕶��'/'���o�Ă����ԍŌ�̕���������
	pos1 = exceptExt.rfind('/');
	if (pos1 != std::wstring::npos)
	{
		// ��؂蕶���̑O�܂ł��f�B���N�g���p�X�Ƃ��ĕۑ�
		directoryPath = exceptExt.substr(0, pos1 + 1);
		// ��؂蕶���̌����t�@�C�����Ƃ��ĕۑ�
		fileName = exceptExt.substr(pos1 + 1, filePath_.size() - pos1 - 1);
		return;
	}
	// ��؂蕶�����Ȃ��̂Ńt�@�C�����݂̂Ƃ��Ĉ���
	directoryPath = L"";
	fileName = exceptExt;
}

void TextureConverter::SaveDDSTextureToFile()
{
	// �ǂݍ��񂾃e�N�X�`����SRGB�Ƃ��Ĉ���
	metadata.format = MakeSRGB(metadata.format);
	
	// �o�̓t�@�C������ݒ肷��
	std::wstring filePath = directoryPath + fileName + L".dds";
	
	// DDS�t�@�C�������o��
	//HRESULT result = SaveToDDSFile(scratchImage.GetImages(), 
	//	scratchImage.GetImageCount(), metadata, DDS_FLAGS_NONE, filePath.c_str());
	//assert(SUCCEEDED(result));
}

void TextureConverter::ConvertTextureWICToDDS(const std::string& filePath)
{
	// �e�N�X�`���t�@�C����ǂݍ���
	LoadWICTextureFromFile(filePath);
	
	// DDS�`���ɕϊ����ď����o��
	SaveDDSTextureToFile();
}