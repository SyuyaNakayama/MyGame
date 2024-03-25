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
	// フルパス
	const std::string fullpath = JsonLoader::DEFAULT_BASE_DIRECTORY + "constant.json";
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
}
