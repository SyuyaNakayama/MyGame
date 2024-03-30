#include "JsonLoader.h"
#include <fstream>
#include <cassert>
using namespace WristerEngine;

const std::string JsonLoader::DEFAULT_BASE_DIRECTORY = "Resources/levels/";

nlohmann::json WristerEngine::JsonLoader::LoadJson(const std::string& fileName)
{	
	// �t���p�X
	const std::string fullpath = DEFAULT_BASE_DIRECTORY + fileName + ".json";
	std::ifstream file; // �t�@�C���X�g���[��
	// �t�@�C�����J��
	file.open(fullpath);
	// �ǂݍ��ݎ��s�̎�
	if (file.fail()) { assert(0); }

	// JSON�����񂩂�𓀂����f�[�^
	nlohmann::json deserialized;
	// ��
	file >> deserialized;
	file.close();
	return deserialized;
}
