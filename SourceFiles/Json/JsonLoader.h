#pragma once
#include <json.hpp>
#include "Model.h"

struct ColliderData
{
	std::string type;
	Vector3 center, size;
};

struct ObjectData : public WorldTransform
{
	std::string fileName;
	std::unique_ptr<Model> model;
	ColliderData collider;
	void Draw() { model->Draw(*this); }
};

struct LevelData
{
	std::list<ObjectData> objects;

	void LoadJsonRecursive(nlohmann::json& object, WorldTransform* parent = nullptr);
	void Draw() { for (auto& obj : objects) { obj.Draw(); } }
};

class JsonLoader
{
private:
	const static std::string DEFAULT_BASE_DIRECTORY;

public:
	/// <param name = "fileName">Šg’£Žq‚È‚µ•¶Žš—ñ< / param>
	static LevelData* LoadJson(const std::string& fileName);
};