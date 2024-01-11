#pragma once
#pragma warning(push)
#pragma warning(disable:4459)
#include <json.hpp>
#pragma warning(pop)
#include "Object3d.h"

namespace WristerEngine
{
	// �R���C�_�[���
	struct ColliderData
	{
		std::string type;
		Vector3 center, size, normal;
	};

	// �I�u�W�F�N�g���
	struct ObjectData
	{
		std::string fileName;
		ColliderData collider;
		WorldTransform* worldTransform;
		int spawnInterval; // �X�|�[���p�x(SpawnObject�N���X��p�ϐ�)
	};

	// ���x���f�[�^
	struct LevelData
	{
		std::list<ObjectData> objects;

		void LoadJsonRecursive(nlohmann::json& object, WorldTransform* parent = nullptr);
	};

	// Json�t�@�C���ǂݍ��݃N���X
	class JsonLoader
	{
	private:
		const static std::string DEFAULT_BASE_DIRECTORY;

	public:
		/// <summary>
		/// Json�t�@�C���ǂݍ���
		/// </summary>
		/// <param name = "fileName">�g���q�Ȃ��t�@�C����������</param>
		/// <returns>�ǂݍ���Json�t�@�C�������ɍ쐬���ꂽ���x���f�[�^</returns>
		static LevelData* LoadJson(const std::string& fileName);
	};
}