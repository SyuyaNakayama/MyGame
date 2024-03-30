#pragma once
#include <unordered_map>
#include <string>
#include "BaseJsonLoader.h"

namespace WristerEngine
{
	// �萔�̏���"constant.json"����ǂݎ��
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

		// �萔��ǂݍ���
		void LoadConstant();

		int GetConstant(const std::string& name);
	};
}