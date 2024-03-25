#include "Constant.h"
#include <fstream>

using namespace WristerEngine;

Constant* Constant::GetInstance()
{
	static Constant instance;
	return &instance;
}

void Constant::LoadConstant()
{
	// �t���p�X
	const std::string fullpath = JsonLoader::DEFAULT_BASE_DIRECTORY + "constant.json";
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
}
