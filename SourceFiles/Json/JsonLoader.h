#pragma once
#include <json.hpp>
#include "Model.h"

struct LevelData
{
	struct ObjectData : public WorldTransform
	{
		std::string fileName;
		std::unique_ptr<Model> model;
		void Draw() { model->Draw(*this); }
	};

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