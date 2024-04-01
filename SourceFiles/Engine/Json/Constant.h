#pragma once
#include <unordered_map>
#include "JsonLoader.h"
#include <cassert>
#include "Vector.h"

namespace WristerEngine
{
	// �萔�̏���"constant.json"����ǂݎ��
	class Constant : public WristerEngine::JsonLoader
	{
	private:
		std::unordered_map<std::string, const void*> constants;
		nlohmann::json deserialized;

		Constant() = default;
		~Constant() = default;

		// �^�ʓǂݍ���
		void LoadInt();
		void LoadFloat();
		void LoadVector();
		void LoadColor();
		void LoadStruct();

	public:
		Constant(const Constant& obj) = delete;
		Constant& operator=(const Constant& obj) = delete;

		static Constant* GetInstance();

		// �萔��ǂݍ���
		void LoadConstants();

		template<class T>
		T GetConstant(const std::string& name)
		{
			T* num = (T*)constants[name];
			assert(num);
			return *num;
		}

		// �I������
		void Finalize();
	};
}