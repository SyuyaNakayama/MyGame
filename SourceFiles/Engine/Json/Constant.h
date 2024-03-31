#pragma once
#include <unordered_map>
#include "JsonLoader.h"
#include <cassert>
#include "Vector.h"

namespace WristerEngine
{
	// 定数の情報を"constant.json"から読み取る
	class Constant : public WristerEngine::JsonLoader
	{
	private:
		std::unordered_map<std::string, const void*> constants;
		nlohmann::json deserialized;

		Constant() = default;
		~Constant() = default;

		// 型別読み込み
		void LoadInt();
		void LoadFloat();
		void LoadVector();
		void LoadColor();
		void LoadStruct();

	public:
		Constant(const Constant& obj) = delete;
		Constant& operator=(const Constant& obj) = delete;

		static Constant* GetInstance();

		// 定数を読み込む
		void LoadConstants();

		template<class T>
		T GetConstant(const std::string& name)
		{
			T* num = (T*)constants[name];
			assert(num);
			return *num;
		}

		// 終了処理
		void Finalize();
	};
}