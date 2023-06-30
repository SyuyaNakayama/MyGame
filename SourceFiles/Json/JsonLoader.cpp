#include "JsonLoader.h"
#include <fstream>
#include <cassert>

const std::string JsonLoader::DEFAULT_BASE_DIRECTORY = "Resources/";

void LevelData::LoadJsonRecursive(nlohmann::json& object, WorldTransform* parent)
{
	// 種別を取得
	std::string type = object["type"].get<std::string>();

	// MESH
	if (type.compare("MESH") == 0)
	{
		// 要素追加
		objects.emplace_back(LevelData::ObjectData{});
		// 今追加した要素の参照を得る
		ObjectData& objectData = objects.back();

		if (object.contains("file_name"))
		{
			// ファイル名
			objectData.fileName = object["file_name"];
		}

		// 親子関係を作る
		objectData.parent = parent;
		// トランスフォームのパラメータ読み込み
		nlohmann::json& transform = object["transform"];
		// 平行移動
		objectData.translation.x = (float)transform["translation"][1];
		objectData.translation.y = (float)transform["translation"][2];
		objectData.translation.z = -(float)transform["translation"][0];
		// 回転角
		objectData.rotation.x = -(float)transform["rotation"][1];
		objectData.rotation.y = -(float)transform["rotation"][2];
		objectData.rotation.z = (float)transform["rotation"][0];
		// 平行移動
		objectData.scale.x = (float)transform["scaling"][1];
		objectData.scale.y = (float)transform["scaling"][2];
		objectData.scale.z = (float)transform["scaling"][0];
		// 初期化
		if (objectData.fileName.empty()) { objectData.fileName = "cube"; }
		objectData.model = Model::Create(objectData.fileName);
		objectData.Initialize();
		objectData.Update();

		// 再帰呼出で枝を走査する
		if (object.contains("children"))
		{
			nlohmann::json children = object["children"].get<nlohmann::json>();
			for (nlohmann::json child : children)
			{
				LoadJsonRecursive(child, &objectData);
			}
		}
	}
}

LevelData* JsonLoader::LoadJson(const std::string& fileName)
{
	// フルパス
	const std::string fullpath = DEFAULT_BASE_DIRECTORY + fileName + ".json";
	std::ifstream file; // ファイルストリーム
	// ファイルを開く
	file.open(fullpath);
	// 読み込み失敗の時
	if (file.fail()) { assert(0); }

	// JSON文字列から解凍したデータ
	nlohmann::json deserialized;
	// 解凍
	file >> deserialized;
	file.close();
	// 正しいレベルデータファイルかチェック
	assert(deserialized.is_object());
	assert(deserialized.contains("name"));
	assert(deserialized["name"].is_string());
	// "name"を文字列として取得
	std::string name = deserialized["name"].get<std::string>();
	// 正しいレベルデータファイルかチェック
	assert(name.compare("scene") == 0);

	// レベルデータ格納用インスタンスを生成
	LevelData* levelData = new LevelData();
	// "object"の全オブジェクトを走査
	for (nlohmann::json& object : deserialized["objects"])
	{
		assert(object.contains("type"));
		levelData->LoadJsonRecursive(object);
	}

	return levelData;
}