#pragma once
#include <unordered_map>
#include <string>
#include "BaseJsonLoader.h"

namespace WristerEngine
{
	// 定数の情報を"constant.json"から読み取る
	class Constant : public WristerEngine::BaseJsonLoader
	{
	private:
		std::unordered_map<std::string, void*> constants;
		
		Constant() = default;
		~Constant() = default;

	public:
		Constant(const Constant& obj) = delete;
		Constant& operator=(const Constant& obj) = delete;

		static Constant* GetInstance();

		// 定数を読み込む
		void LoadConstant();

		int GetConstant(const std::string& name);
	};
}