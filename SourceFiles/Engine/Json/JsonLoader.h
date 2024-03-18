#pragma once
#pragma warning(push)
#pragma warning(disable:26800)
#pragma warning(disable:26819)
#include <json.hpp>
#pragma warning(pop)
#include "Object3d.h"

enum class ObjectType
{
	White,	// �ʏ�
	Red,	// �_��2�{
	Green,	// �_��-1�{
};

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
		_3D::Transform* worldTransform = nullptr;
		int spawnInterval = 0; // �X�|�[���p�x(SpawnObject�N���X��p�ϐ�)
		int spawnMax = 0; // �X�|�[���ő吔(SpawnObject�N���X��p�ϐ�)
		ObjectType objectType = ObjectType::White;
	};

	// ���x���f�[�^
	struct LevelData
	{
		std::list<ObjectData> objects;

		void LoadJsonRecursive(nlohmann::json& object, _3D::Transform* parent = nullptr);
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