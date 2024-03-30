#include "LevelLoader.h"
#include <cassert>
#include "ModelManager.h"
using namespace WristerEngine::_3D;

void LevelData::LoadLevelRecursive(nlohmann::json& object, Transform* parent)
{
	// 種別を取得
	std::string type = object["type"].get<std::string>();

	// MESH
	if (type.compare("MESH") == 0)
	{
		// 要素追加
		objects.emplace_back(ObjectData{});
		// 今追加した要素の参照を得る
		ObjectData& objectData = objects.back();

		if (object.contains("file_name"))
		{
			// ファイル名
			objectData.fileName = object["file_name"];
		}

		// 初期化
		if (objectData.fileName.empty()) { objectData.fileName = "cube"; }
		objectData.worldTransform = new Transform;
		objectData.worldTransform->Initialize();
		Transform* worldTransform = objectData.worldTransform;

		// 親子関係を作る
		worldTransform->parent = parent;
		// トランスフォームのパラメータ読み込み
		nlohmann::json& transform = object["transform"];
		// 平行移動
		worldTransform->translation.x = (float)transform["translation"][1];
		worldTransform->translation.y = (float)transform["translation"][2];
		worldTransform->translation.z = -(float)transform["translation"][0];
		// 回転角
		worldTransform->rotation.x = -(float)transform["rotation"][1];
		worldTransform->rotation.y = -(float)transform["rotation"][2];
		worldTransform->rotation.z = (float)transform["rotation"][0];
		// スケーリング
		worldTransform->scale.x = (float)transform["scaling"][1];
		worldTransform->scale.y = (float)transform["scaling"][2];
		worldTransform->scale.z = (float)transform["scaling"][0];

		// コライダーのパラメータ読み込み
		if (object.contains("collider"))
		{
			nlohmann::json& collider = object["collider"];
			// 形状
			objectData.collider.type = collider["type"];
			// 中心
			objectData.collider.center.x = (float)collider["center"][1];
			objectData.collider.center.y = (float)collider["center"][2];
			objectData.collider.center.z = -(float)collider["center"][0];
			// サイズ
			objectData.collider.size.x = (float)collider["size"][1];
			objectData.collider.size.y = (float)collider["size"][2];
			objectData.collider.size.z = (float)collider["size"][0];
			// 法線ベクトル
			objectData.collider.normal.x = -(float)collider["normal"][1];
			objectData.collider.normal.y = (float)collider["normal"][2];
			objectData.collider.normal.z = (float)collider["normal"][0];
		}
	}
	// 再帰呼出で枝を走査する
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
		levelData->LoadLevelRecursive(object);
	}

	return levelData;
}