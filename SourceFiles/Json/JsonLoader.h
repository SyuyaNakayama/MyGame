#pragma once
#include <json.hpp>
#include "Model.h"

struct LevelData
{
	struct ObjectData : public WorldTransform
	{
		std::string fileName;
		std::unique_ptr<Model> model;
		void Initialize();
		void Draw();
	};

	std::vector<ObjectData> objects;

	void LoadJsonRecursive(nlohmann::json& deserialized);
	void Initialize() { for (auto& obj : objects) { obj.Initialize(); } }
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