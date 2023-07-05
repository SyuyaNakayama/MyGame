#include "JsonLoader.h"
#include <fstream>
#include <cassert>

const std::string JsonLoader::DEFAULT_BASE_DIRECTORY = "Resources/levels/";

void LevelData::LoadJsonRecursive(nlohmann::json& object, WorldTransform* parent)
{
	// ��ʂ��擾
	std::string type = object["type"].get<std::string>();

	// MESH
	if (type.compare("MESH") == 0)
	{
		// �v�f�ǉ�
		objects.emplace_back(ObjectData{});
		// ���ǉ������v�f�̎Q�Ƃ𓾂�
		ObjectData& objectData = objects.back();

		if (object.contains("file_name"))
		{
			// �t�@�C����
			objectData.fileName = object["file_name"];
		}

		// �e�q�֌W�����
		objectData.parent = parent;
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
		// �X�P�[�����O
		objectData.scale.x = (float)transform["scaling"][1];
		objectData.scale.y = (float)transform["scaling"][2];
		objectData.scale.z = (float)transform["scaling"][0];
		
		// �R���C�_�[�̃p�����[�^�ǂݍ���
		if (object.contains("collider"))
		{
			nlohmann::json& collider = object["collider"];
			// �`��
			objectData.collider.type = collider["type"];
			// ���S
			objectData.collider.center.x = (float)collider["center"][1];
			objectData.collider.center.y = (float)collider["center"][2];
			objectData.collider.center.z = -(float)collider["center"][0];
			// �T�C�Y
			objectData.collider.size.x = (float)collider["size"][1];
			objectData.collider.size.y = (float)collider["size"][2];
			objectData.collider.size.z = (float)collider["size"][0];
			// �@���x�N�g��
			objectData.collider.normal.x = -(float)collider["normal"][1];
			objectData.collider.normal.y = (float)collider["normal"][2];
			objectData.collider.normal.z = (float)collider["normal"][0];
		}
		// ������
		if (objectData.fileName.empty()) { objectData.fileName = "cube"; }
		objectData.Initialize();
		objectData.Update();
	}
	// �ċA�ďo�Ŏ}�𑖍�����
	if (object.contains("children"))
	{
		nlohmann::json children = object["children"].get<nlohmann::json>();
		ObjectData& objectData = objects.back();
		for (nlohmann::json child : children)
		{
			LoadJsonRecursive(child, &objectData);
		}
	}
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
	// "object"�̑S�I�u�W�F�N�g�𑖍�
	for (nlohmann::json& object : deserialized["objects"])
	{
		assert(object.contains("type"));
		levelData->LoadJsonRecursive(object);
	}

	return levelData;
}