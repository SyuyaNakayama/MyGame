#pragma once
#include <json.hpp>
#include "Model.h"

struct ColliderData
{
	std::string type;
	Vector3 center, size, normal;
};

struct ObjectData : public WorldTransform
{
	std::string fileName;
	ColliderData collider;
};

struct LevelData
{
	std::list<ObjectData> objects;

	void LoadJsonRecursive(nlohmann::json& object, WorldTransform* parent = nullptr);
};

class JsonLoader
{
private:
	const static std::string DEFAULT_BASE_DIRECTORY;

public:
	/// <param name = "fileName">Šg’£Žq‚È‚µ•¶Žš—ñ< / param>
	static LevelData* LoadJson(const std::string& fileName);
};