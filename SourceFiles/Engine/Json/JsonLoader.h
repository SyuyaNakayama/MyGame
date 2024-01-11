#pragma once
#pragma warning(push)
#pragma warning(disable:4459)
#include <json.hpp>
#pragma warning(pop)
#include "Object3d.h"

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
		WorldTransform* worldTransform;
		int spawnInterval; // スポーン頻度(SpawnObjectクラス専用変数)
	};

	// レベルデータ
	struct LevelData
	{
		std::list<ObjectData> objects;

		void LoadJsonRecursive(nlohmann::json& object, WorldTransform* parent = nullptr);
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