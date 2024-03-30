#include "Constant.h"
#include <fstream>

using namespace WristerEngine;

Constant* Constant::GetInstance()
{
	static Constant instance;
	return &instance;
}

void Constant::LoadConstant()
{
	nlohmann::json deserialized = LoadJson("constant");

	for (auto& object : deserialized["int"])
	{
		const auto& list = object.get<std::map<std::string, int>>();
		for (const auto& val : list)
		{
			constants[val.first] = new int(val.second);
		}
	}
}

int WristerEngine::Constant::GetConstant(const std::string& name)
{
	int* num = (int*)constants[name];
	return *num;
}