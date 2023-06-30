#include "JsonLoader.h"
#include <fstream>
#include <cassert>

const std::string JsonLoader::DEFAULT_BASE_DIRECTORY = "Resources/";

void LevelData::LoadJsonRecursive(nlohmann::json& deserialized)
{
	// "object"�̑S�I�u�W�F�N�g�𑖍�
	for (nlohmann::json& object : deserialized["objects"])
	{
		assert(object.contains("type"));

		// ��ʂ��擾
		std::string type = object["type"].get<std::string>();

		// MESH
		if (type.compare("MESH") == 0)
		{
			// �v�f�ǉ�
			objects.emplace_back(LevelData::ObjectData{});
			// ���ǉ������v�f�̎Q�Ƃ𓾂�
			ObjectData& objectData = objects.back();

			if (object.contains("file_name"))
			{
				// �t�@�C����
				objectData.fileName = object["file_name"];
			}

			// �g�����X�t�H�[���̃p�����[�^�ǂݍ���
			nlohmann::json& transform = object["transform"];
			// ���s�ړ�
			objectData.translation.x = (float)transform["translation"][1];
			objectData.translation.y = (float)transform["translation"][2];
			objectData.translation.z = -(float)transform["translation"][0];
			// ��]�p
			objectData.rotation.x = -(float)transform["rotation"][1];
			objectData.rotation.y = -(float)transform["rotation"][2];
			objectData.rotation.z = (float)transform["rotation"][0];
			// ���s�ړ�
			objectData.scale.x = (float)transform["scaling"][1];
			objectData.scale.y = (float)transform["scaling"][2];
			objectData.scale.z = (float)transform["scaling"][0];
		}
	}
}

void LevelData::ObjectData::Initialize()
{
	if (fileName.empty()) { fileName = "cube"; }
	model = Model::Create(fileName);
	WorldTransform::Initialize();
	WorldTransform::Update();
}

void LevelData::ObjectData::Draw()
{
	model->Draw(*this);
}

LevelData* JsonLoader::LoadJson(const std::string& fileName)
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
	// ���������x���f�[�^�t�@�C�����`�F�b�N
	assert(deserialized.is_object());
	assert(deserialized.contains("name"));
	assert(deserialized["name"].is_string());
	// "name"�𕶎���Ƃ��Ď擾
	std::string name = deserialized["name"].get<std::string>();
	// ���������x���f�[�^�t�@�C�����`�F�b�N
	assert(name.compare("scene") == 0);

	// ���x���f�[�^�i�[�p�C���X�^���X�𐶐�
	LevelData* levelData = new LevelData();

	levelData->LoadJsonRecursive(deserialized);

	// "object"�̑S�I�u�W�F�N�g�𑖍�
	//for (nlohmann::json& object : deserialized["objects"])
	//{
	//	assert(object.contains("type"));

	//	// ��ʂ��擾
	//	std::string type = object["type"].get<std::string>();

	//	// MESH
	//	if (type.compare("MESH") == 0)
	//	{
	//		// �v�f�ǉ�
	//		levelData->objects.emplace_back(LevelData::ObjectData{});
	//		// ���ǉ������v�f�̎Q�Ƃ𓾂�
	//		LevelData::ObjectData& objectData = levelData->objects.back();

	//		if(object.contains("file_name"))
	//		{
	//			// �t�@�C����
	//			objectData.fileName = object["file_name"];
	//		}

	//		// �g�����X�t�H�[���̃p�����[�^�ǂݍ���
	//		nlohmann::json& transform = object["transform"];
	//		// ���s�ړ�
	//		objectData.translation.x = (float)transform["translation"][1];
	//		objectData.translation.y = (float)transform["translation"][2];
	//		objectData.translation.z = -(float)transform["translation"][0];
	//		// ��]�p
	//		objectData.rotation.x = -(float)transform["rotation"][1];
	//		objectData.rotation.y = -(float)transform["rotation"][2];
	//		objectData.rotation.z = (float)transform["rotation"][0];
	//		// ���s�ړ�
	//		objectData.scale.x = (float)transform["scaling"][1];
	//		objectData.scale.y = (float)transform["scaling"][2];
	//		objectData.scale.z = (float)transform["scaling"][0];
	//	}
	//}

	levelData->Initialize();
	return levelData;
}