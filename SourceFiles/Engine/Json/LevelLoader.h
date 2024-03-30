#pragma once
#include "Object3d.h"
#include "JsonLoader.h"

enum class ObjectType
{
	White,	// 通常
	Red,	// 点数2倍
	Green,	// 点数-1倍
};

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
	WristerEngine::_3D::Transform* worldTransform = nullptr;
	int spawnInterval = 0; // スポーン頻度(SpawnObjectクラス専用変数)
	int spawnMax = 0; // スポーン最大数(SpawnObjectクラス専用変数)
	ObjectType objectType = ObjectType::White;
};

// レベルデータ
struct LevelData
{
	std::list<ObjectData> objects;

	void LoadLevelRecursive(nlohmann::json& object, WristerEngine::_3D::Transform* parent = nullptr);
};

// Jsonファイル読み込みクラス
class LevelLoader : public WristerEngine::JsonLoader
{
public:
	/// <summary>
	/// Jsonファイル読み込み
	/// </summary>
	/// <param name = "fileName">拡張子なしファイル名文字列</param>
	/// <returns>読み込んだJsonファイルを元に作成されたレベルデータ</returns>
	static LevelData* LoadLevel(const std::string& fileName);
};