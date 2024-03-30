#include "LevelLoader.h"
#include <cassert>
#include "ModelManager.h"
using namespace WristerEngine::_3D;

void LevelData::LoadLevelRecursive(nlohmann::json& object, Transform* parent)
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

		// ������
		if (objectData.fileName.empty()) { objectData.fileName = "cube"; }
		objectData.worldTransform = new Transform;
		objectData.worldTransform->Initialize();
		Transform* worldTransform = objectData.worldTransform;

		// �e�q�֌W�����
		worldTransform->parent = parent;
		// �g�����X�t�H�[���̃p�����[�^�ǂݍ���
		nlohmann::json& transform = object["transform"];
		// ���s�ړ�
		worldTransform->translation.x = (float)transform["translation"][1];
		worldTransform->translation.y = (float)transform["translation"][2];
		worldTransform->translation.z = -(float)transform["translation"][0];
		// ��]�p
		worldTransform->rotation.x = -(float)transform["rotation"][1];
		worldTransform->rotation.y = -(float)transform["rotation"][2];
		worldTransform->rotation.z = (float)transform["rotation"][0];
		// �X�P�[�����O
		worldTransform->scale.x = (float)transform["scaling"][1];
		worldTransform->scale.y = (float)transform["scaling"][2];
		worldTransform->scale.z = (float)transform["scaling"][0];

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
	}
	// �ċA�ďo�Ŏ}�𑖍�����
	if (object.contains("children"))
	{
		nlohmann::json children = object["children"].get<nlohmann::json>();
		ObjectData& objectData = objects.back();
		for (nlohmann::json child : children)
		{
			LoadLevelRecursive(child, objectData.worldTransform);
		}
	}
}

LevelData* LevelLoader::LoadLevel(const std::string& fileName)
{
	nlohmann::json deserialized = LoadJson(fileName);

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
		levelData->LoadLevelRecursive(object);
	}

	return levelData;
}