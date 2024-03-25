#pragma once
#include <unordered_map>
#include <string>
#include <JsonLoader.h>

namespace WristerEngine
{
	// ’è”‚Ìî•ñ‚ğ"constant.json"‚©‚ç“Ç‚İæ‚é
	class Constant
	{
	private:
		std::unordered_map<std::string, void*> constants;
		
		Constant() = default;
		~Constant() = default;

	public:
		Constant(const Constant& obj) = delete;
		Constant& operator=(const Constant& obj) = delete;

		static Constant* GetInstance();

		// ’è”‚ğ“Ç‚İ‚Ş
		void LoadConstant();
	};
}