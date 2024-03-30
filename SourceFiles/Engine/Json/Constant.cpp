#include "Constant.h"
#include "Color.h"
#include <fstream>

using namespace WristerEngine;

Constant* Constant::GetInstance()
{
	static Constant instance;
	return &instance;
}

void WristerEngine::Constant::LoadInt()
{
	if (!deserialized.contains("int")) { return; }
	// �萔���X�g�擾�ƃC���X�^���X����(int)
	const auto& list = deserialized["int"].get<std::map<std::string, int>>();
	for (const auto& val : list) { constants[val.first] = new int(val.second); }
}

void WristerEngine::Constant::LoadFloat()
{
	if (!deserialized.contains("float")) { return; }
	// �萔���X�g�擾�ƃC���X�^���X����(float)
	const auto& list = deserialized["float"].get<std::map<std::string, float>>();
	for (const auto& val : list) { constants[val.first] = new int(val.second); }
}

void WristerEngine::Constant::LoadVector()
{
	if (deserialized.contains("Vector2"))
	{
		// �萔���X�g�擾�ƃC���X�^���X����(Vector2)
		const auto& list = deserialized["Vector2"].get<std::map<std::string, std::vector<float>>>();
		for (const auto& val : list) { constants[val.first] = new Vector2(val.second[0], val.second[1]); }
	}

	if (deserialized.contains("Vector3"))
	{
		// �萔���X�g�擾�ƃC���X�^���X����(Vector3)
		const auto& list = deserialized["Vector3"].get<std::map<std::string, std::vector<float>>>();
		for (const auto& val : list) { constants[val.first] = new Vector3(val.second[0], val.second[1], val.second[2]); }
	}
}

void WristerEngine::Constant::LoadColor()
{
	if (deserialized.contains("ColorRGB"))
	{
		// �萔���X�g�擾�ƃC���X�^���X����(ColorRGB)
		const auto& list = deserialized["ColorRGB"].get<std::map<std::string, std::vector<float>>>();
		for (const auto& val : list) { constants[val.first] = new ColorRGB(val.second[0], val.second[1], val.second[2]); }
	}

	if (deserialized.contains("ColorRGBA"))
	{
		// �萔���X�g�擾�ƃC���X�^���X����(ColorRGBA)
		const auto& list = deserialized["ColorRGBA"].get<std::map<std::string, std::vector<float>>>();
		for (const auto& val : list) { constants[val.first] = new ColorRGBA(val.second[0], val.second[1], val.second[2], val.second[3]); }
	}
}

void Constant::LoadConstants()
{
	deserialized = LoadJson("constant");

	LoadInt();
	LoadFloat();
	LoadVector();
	LoadColor();
}

void WristerEngine::Constant::Finalize()
{
	for (auto& p : constants)
	{
		// ���������
		delete p.second;
		p.second = nullptr;
	}
	constants.clear();
}