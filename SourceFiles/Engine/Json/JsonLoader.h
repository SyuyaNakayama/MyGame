#pragma once
#pragma warning(push)
#pragma warning(disable:26800)
#pragma warning(disable:26819)
#include <json.hpp>
#pragma warning(pop)
#include "Object3d.h"

enum class ObjectType
{
	White,	// 通常
	Red,	// 点数2倍
	Green,	// 点数-1倍
};

namespace WristerEngine
{
	// コライダー情報
	struct ColliderData
	{
		std::string type;
		Vector3 center, size, normal;
	};

	// オブジェクト情報
	struct ObjectData
	{
		std::string fileName;
		ColliderData collider;
		_3D::Transform* worldTransform = nullptr;
		int spawnInterval = 0; // スポーン頻度(SpawnObjectクラス専用変数)
		int spawnMax = 0; // スポーン最大数(SpawnObjectクラス専用変数)
		ObjectType objectType = ObjectType::White;
	};

	// レベルデータ
	struct LevelData
	{
		std::list<ObjectData> objects;

		void LoadJsonRecursive(nlohmann::json& object, _3D::Transform* parent = nullptr);
	};

	// Jsonファイル読み込みクラス
	class JsonLoader
	{
	private:
		const static std::string DEFAULT_BASE_DIRECTORY;

	public:
		/// <summary>
		/// Jsonファイル読み込み
		/// </summary>
		/// <param name = "fileName">拡張子なしファイル名文字列</param>
		/// <returns>読み込んだJsonファイルを元に作成されたレベルデータ</returns>
		static LevelData* LoadJson(const std::string& fileName);
	};
}